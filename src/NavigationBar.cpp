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

#include "NavigationBar.h"
#include "NavigationBar_p.h"
#include <QHBoxLayout>
#include <QPaintEvent>
#include <QPainter>

/*!
 * \class NavigationBar
 * \inmodule FlatGui
 */

NavigationBar::NavigationBar(QWidget *parent) :
	AbstractPanel(parent),
	m_ptr(new NavigationBarPrivate)
{
	QHBoxLayout *layoutMain = new QHBoxLayout(this);
	QFont f{QFont()};

	layoutMain->setSizeConstraint(QLayout::SetMinimumSize);
	layoutMain->setContentsMargins(0, 0, 0, 0);
	layoutMain->setSpacing(0);

	f.setBold(true);

	setFixedHeight(48);
	setFont(f);
	setBackgroundRole(QPalette::Dark);
	setAutoFillBackground(true);
}

NavigationBar::~NavigationBar()
{
	delete m_ptr;
}

void NavigationBar::setTitle(const QString &title)
{
	m_ptr->title = title.toUpper();
	m_ptr->titleWidth = fontMetrics().horizontalAdvance(m_ptr->title);

	update();
}

void NavigationBar::paintEvent(QPaintEvent *event)
{
	QPainter painter(this);
	const int w = width(), minWidth = 192 + m_ptr->titleWidth;

	painter.setClipping(true);
	painter.setClipRect(event->rect());

	painter.setPen(palette().color(QPalette::HighlightedText));
	painter.setOpacity(w <= minWidth ? 0.0 : w >= minWidth + 48
									   ? 1.0 : (w - minWidth)/48.0);
	painter.drawText(QRect(0, 0, w, 48), Qt::AlignCenter, m_ptr->title);
}

NavigationBarPrivate::NavigationBarPrivate() :
	titleWidth(0)
{

}
