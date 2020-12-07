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

#include "SToolButton.h"
#include "SToolButton_p.h"
#include <QPaintEvent>
#include <QPainter>

/*!
	\class SToolButton
	\inmodule Components
	\ingroup Buttons
 */

SToolButton::SToolButton(QWidget *parent) :
	SAbstractButton(parent),
	m_ptr(new SToolButtonPrivate)
{
	setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
}

SToolButton::~SToolButton()
{
	delete m_ptr;
}

void SToolButton::setPixmap(const QPixmap &pixmap)
{
	m_ptr->pixmap = pixmap;
	update();
}

/*!
 * \brief SToolButton::setSize
 */

void SToolButton::setSize(int n)
{
	m_ptr->pixmapOrigin.setX((n - m_ptr->pixmap.width())/2);
	m_ptr->pixmapOrigin.setY((n - m_ptr->pixmap.height())/2);
	m_ptr->scaleFactor = 1 - 5.0/n;

	resize(n, n);
	setFixedSize(n, n);
}

/*!
 * \brief Handles the painting of the SToolButton by drawing its content on a
 * canvas.
 *
 * When the button is pressed a visual confirmation for the user is created by
 * scaling the canvas and lowering its opacity. This event handler implements
 * the Template Method design pattern and depends on the subclasses to define
 * how the button will look like by letting them do the actual painting.
 *
 * \sa SToolButton::paint
 * \reimp
 */

void SToolButton::paintEvent(QPaintEvent *event)
{
	QPainter painter(this);
	bool clickable = isEnabled();

	painter.setClipping(true);
	painter.setClipRect(event->rect());
	painter.setRenderHint(QPainter::SmoothPixmapTransform);

	QPixmap canvas(size());
	QPainter canvasPainter;

	canvas.fill(Qt::transparent);

	canvasPainter.begin(&canvas);

	painter.setOpacity(clickable ? 1 : 0.25);

	paint(&canvasPainter);

	if (clickable && isDown()) {
		painter.setOpacity(0.9);
		painter.translate(rect().center());
		painter.scale(m_ptr->scaleFactor, m_ptr->scaleFactor);
		painter.translate(-rect().center());
	}

	painter.drawPixmap(rect(), canvas);
}

/*!
 * \brief SToolButton::paint
 */

void SToolButton::paint(QPainter *painter)
{
	painter->drawPixmap(m_ptr->pixmapOrigin, m_ptr->pixmap);
}

void SToolButton::setPixmapOrigin(const QPoint &p)
{
	m_ptr->pixmapOrigin = p;
}

void SToolButton::setScaleFactor(qreal d)
{
	m_ptr->scaleFactor = d;
}

SToolButtonPrivate::SToolButtonPrivate() :
	scaleFactor(0.9)
{

}
