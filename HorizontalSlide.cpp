/**
MIT License

Copyright (c) 2018 Michael Scopchanov

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

#include "HorizontalSlide.h"
#include <QVariantAnimation>
#include <QLabel>

HorizontalSlide::HorizontalSlide(QWidget *parent) :
	QObject(parent),
	m_parentWidget(parent),
	m_currentPage(nullptr),
	m_nextPage(nullptr),
	m_labCurrent(new QLabel(parent)),
	m_labNext(new QLabel(parent)),
	m_width(parent->width()),
	m_height(parent->height()),
	m_slideLeft(false)
{
	m_labCurrent->setStyleSheet(".QLabel { padding: 0; }");

	m_labNext->move(m_width, 0);
	m_labNext->setStyleSheet(".QLabel { padding: 0; }");
}

void HorizontalSlide::setCurrentPage(QWidget *currentPage)
{
	QPixmap pixmap(m_width, m_height);

	m_currentPage = currentPage;
	m_currentPage->hide();
	m_currentPage->render(&pixmap);

	m_labCurrent->setPixmap(pixmap);
}

QWidget *HorizontalSlide::nextPage() const
{
	return m_nextPage;
}

void HorizontalSlide::setNextPage(QWidget *nextPage)
{
	QPixmap pixmap(m_width, m_height);

	m_nextPage = nextPage;
	m_nextPage->resize(m_width, m_height);
	m_nextPage->render(&pixmap);

	m_labNext->setPixmap(pixmap);
}

void HorizontalSlide::start(bool slideLeft, int speed)
{
	QVariantAnimation *animation = new QVariantAnimation(this);

	m_slideLeft = slideLeft;

	m_labCurrent->show();
	m_labNext->show();

	animation->setStartValue(m_slideLeft ? 0 : m_width);
	animation->setEndValue(m_slideLeft ? m_width : 0);
	animation->setDuration(speed);
//	animation->setDuration(5000);
//	animation->setEasingCurve(QEasingCurve::OutBack);
	animation->start(QVariantAnimation::DeleteWhenStopped);

	connect(animation, &QVariantAnimation::valueChanged,
			this, &HorizontalSlide::onValueChanged);
	connect(animation, &QVariantAnimation::finished,
			this, &HorizontalSlide::onAnimationFinished);
}

void HorizontalSlide::onValueChanged(const QVariant &value)
{
	int n = -value.toInt(), m = m_width + n;

	if (m_slideLeft) {
		m_labCurrent->move(n, 0);
		m_labNext->move(m, 0);
	} else {
		m_labCurrent->move(m, 0);
		m_labNext->move(n, 0);
	}

	m_parentWidget->repaint();
}

void HorizontalSlide::onAnimationFinished()
{
	delete m_labCurrent;
	delete m_labNext;

	m_nextPage->show();
	m_nextPage->resize(m_parentWidget->size());

	deleteLater();
	finished();
}
