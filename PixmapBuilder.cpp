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

#include "PixmapBuilder.h"
#include "PixmapBuilder_p.h"
#include <QPainter>
#include <QPixmap>
#include <QColor>

QPixmap PixmapBuilder::create(int type, const QColor &color, int size)
{
	return PixmapBuilder().drawPixmap(type, color, size);
}

PixmapBuilder::PixmapBuilder() :
	m_ptr(new PixmapBuilderPrivate)
{

}

PixmapBuilder::~PixmapBuilder()
{
	delete m_ptr;
}

QPixmap PixmapBuilder::drawPixmap(int type, const QColor &color, int size)
{
	QPixmap pixmap(size, size);
	QPainter painter;

	pixmap.fill(Qt::transparent);

	painter.begin(&pixmap);

	switch (type) {
	case Grid:
		m_ptr->drawGrid(&painter, color);
		break;
	case GridSmall:
		m_ptr->drawGridSmall(&painter, color);
		break;
	case Glass:
		m_ptr->drawGlass(&painter, color);
		break;
	case Cross:
		m_ptr->drawCross(&painter, color);
		break;
	case Back:
		m_ptr->drawBack(&painter, color);
		break;
	case Next:
		m_ptr->drawNext(&painter, color);
		break;
	case Home:
		m_ptr->drawHome(&painter, color);
		break;
	case Menu:
		m_ptr->drawMenu(&painter, color);
		break;
	case Check:
		m_ptr->drawCheck(&painter, color);
		break;
	case Up:
		m_ptr->drawUp(&painter, color);
		break;
	case Down:
		m_ptr->drawDown(&painter, color);
		break;
	case Square:
		m_ptr->drawSquare(&painter, color);
		break;
	case SquareSmall:
		m_ptr->drawSquareSmall(&painter, color);
		break;
	case Info:
		m_ptr->drawInfo(&painter, color);
		break;
	case Warning:
		m_ptr->drawWarning(&painter, color);
		break;
	case Error:
		m_ptr->drawError(&painter, color);
		break;
	}

	return pixmap;
}

PixmapBuilderPrivate::PixmapBuilderPrivate()
{

}

void PixmapBuilderPrivate::drawGrid(QPainter *painter, const QColor &color)
{
	painter->setPen(QPen(color, 3));
	painter->drawPoints(QPolygon(QVector<QPoint>{QPoint(5, 5),
												 QPoint(5, 10),
												 QPoint(10, 5),
												 QPoint(10, 10)}));
}

void PixmapBuilderPrivate::drawGridSmall(QPainter *painter, const QColor &color)
{
	painter->setPen(QPen(color, 3));
	painter->drawPoints(QPolygon(QVector<QPoint>{QPoint(1, 1),
												 QPoint(1, 6),
												 QPoint(6, 1),
												 QPoint(6, 6)}));
}

void PixmapBuilderPrivate::drawGlass(QPainter *painter, const QColor &color)
{
	painter->setRenderHint(QPainter::Antialiasing);
	painter->setPen(QPen(color, 1.6));
	painter->drawEllipse(4, 4, 7, 7);
	painter->drawLine(11, 11, 13, 13);
}

void PixmapBuilderPrivate::drawCross(QPainter *painter, const QColor &color)
{
	painter->setPen(color);
	painter->drawLine(4, 4, 11, 11);
	painter->drawLine(11, 4, 4, 11);
}

void PixmapBuilderPrivate::drawBack(QPainter *painter, const QColor &color)
{
	painter->setPen(QPen(color, 2));
	painter->drawLine(2, 8, 8, 2);
	painter->drawLine(2, 8, 14, 8);
	painter->drawLine(2, 8, 8, 14);
}

void PixmapBuilderPrivate::drawNext(QPainter *painter, const QColor &color)
{
	painter->setPen(QPen(color, 2));
	painter->drawLine(8, 2, 14, 8);
	painter->drawLine(2, 8, 14, 8);
	painter->drawLine(14, 8, 8, 14);
}

void PixmapBuilderPrivate::drawHome(QPainter *painter, const QColor &color)
{
	painter->setPen(QPen(color, 2));
	painter->drawLine(2, 8, 8, 2);
	painter->drawLine(8, 2, 14, 8);
	painter->drawLine(4, 8, 4, 14);
	painter->drawLine(4, 14, 12, 14);
	painter->drawLine(12, 3, 12, 14);
}

void PixmapBuilderPrivate::drawMenu(QPainter *painter, const QColor &color)
{
	painter->setPen(QPen(color, 2));
	painter->drawLine(3, 3, 13, 3);
	painter->drawLine(3, 8, 13, 8);
	painter->drawLine(3, 13, 13, 13);
}

void PixmapBuilderPrivate::drawCheck(QPainter *painter, const QColor &color)
{
	painter->setRenderHint(QPainter::Antialiasing);
	painter->setPen(QPen(color, 2));
	painter->drawLine(2, 8, 5, 11);
	painter->drawLine(6, 11, 12, 4);
}

void PixmapBuilderPrivate::drawUp(QPainter *painter, const QColor &color)
{
	painter->setPen(color);
	painter->drawLine(2, 10, 7, 5);
	painter->drawLine(3, 10, 7, 6);
	painter->drawLine(8, 5, 13, 10);
	painter->drawLine(8, 6, 12, 10);
}

void PixmapBuilderPrivate::drawDown(QPainter *painter, const QColor &color)
{
	painter->setPen(color);
	painter->drawLine(2, 5, 7, 10);
	painter->drawLine(3, 5, 7, 9);
	painter->drawLine(8, 10, 13, 5);
	painter->drawLine(8, 9, 12, 5);
}

void PixmapBuilderPrivate::drawSquare(QPainter *painter, const QColor &color)
{
	painter->fillRect(1, 1, 6, 6, color);
}

void PixmapBuilderPrivate::drawSquareSmall(QPainter *painter, const QColor &color)
{
	painter->fillRect(2, 2, 4, 4, color);
}

void PixmapBuilderPrivate::drawInfo(QPainter *painter, const QColor &color)
{
	QPainterPath circ;
	QPainterPath letter;

	circ.addEllipse(3, 3, 42, 42);

	letter.addRoundedRect(22, 11, 4, 4, 1, 1);
	letter.addRect(21, 18, 5, 3);
	letter.addRect(22, 21, 4, 13);
	letter.addRect(21, 34, 6, 3);

	painter->setRenderHint(QPainter::Antialiasing);
	painter->setPen(Qt::transparent);
	painter->setBrush(color);
	painter->drawPath(circ.subtracted(letter));
}

void PixmapBuilderPrivate::drawWarning(QPainter *painter, const QColor &color)
{
	QPainterPath triangle;
	QPainterPath letter;

	triangle.moveTo(2, 45);
	triangle.lineTo(24, 2);
	triangle.lineTo(45, 45);
	triangle.lineTo(2, 45);

	letter.addRoundedRect(22, 15, 4, 19, 1, 1);
	letter.addRoundedRect(22, 37, 4, 4, 1, 1);

	painter->setRenderHint(QPainter::Antialiasing);
	painter->setPen(Qt::transparent);
	painter->setBrush(color);
	painter->drawPath(triangle.subtracted(letter));
}

void PixmapBuilderPrivate::drawError(QPainter *painter, const QColor &color)
{
	QPainterPath circ;
	QPainterPath cross;
	QTransform t;

	t.translate(24, -10);
	t.rotate(45);

	circ.addEllipse(3, 3, 42, 42);

	cross.addRoundedRect(22, 12, 4, 24, 1, 1);
	cross.addRoundedRect(12, 22, 24, 4, 1, 1);
	cross.setFillRule(Qt::WindingFill);

	painter->setRenderHint(QPainter::Antialiasing);
	painter->setPen(Qt::transparent);
	painter->setBrush(color);
	painter->drawPath(circ.subtracted(t.map(cross)));
}
