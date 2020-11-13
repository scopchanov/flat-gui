/**
MIT License

Copyright (c) 2020 Michael Scopchanov

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#include "PageIndicator.h"
#include <QHBoxLayout>
#include <QLabel>

/*!
 * \class PageIndicator
 * \inmodule FlatGui
 */

PageIndicator::PageIndicator(QWidget *parent) :
	QWidget(parent),
	m_layoutDots(new QHBoxLayout())
{
	QHBoxLayout *layoutMain = new QHBoxLayout(this);

	layoutMain->addStretch();
	layoutMain->addLayout(m_layoutDots);
	layoutMain->addStretch();
	layoutMain->setContentsMargins(0, 0, 0, 0);
	layoutMain->setSpacing(4);

	setAttribute(Qt::WA_StyledBackground);
	setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
	setFixedHeight(24);
}

void PageIndicator::setPixmapActive(const QPixmap &pixmap)
{
	m_pixmapActive = pixmap;
}

void PageIndicator::setPixmapInactive(const QPixmap &pixmap)
{
	m_pixmapInactive = pixmap;
}

void PageIndicator::setCount(int cnt)
{
	int N = m_layoutDots->count();

	if (cnt == N)
		return;

	if (cnt > N) {
		for (int n = 0; n < (cnt - N); n++) {
			auto *label = new QLabel(this);

			label->setPixmap(m_pixmapInactive);
			label->setAlignment(Qt::AlignCenter);
			label->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);

			m_layoutDots->addWidget(label);
		}
	}
	else {
		for (int n = 0; n < N - cnt; n++)
			m_layoutDots->takeAt(m_layoutDots->count() - 1)->widget()->deleteLater();
	}
}

void PageIndicator::setCurrentIndex(int n, int)
{
	for (int m = 0; m < m_layoutDots->count(); m++)
		static_cast<QLabel *>(m_layoutDots->itemAt(m)->widget())
			->setPixmap(m == n ? m_pixmapActive : m_pixmapInactive);
}
