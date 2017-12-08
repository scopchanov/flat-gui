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
