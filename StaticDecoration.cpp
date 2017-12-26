#include "StaticDecoration.h"
#include <QPainter>

/*!
 * \class StaticDecoration
 * \inmodule FlatGui
 */

StaticDecoration::StaticDecoration(QObject *parent) :
	AbstractDecoration(parent)
{

}

void StaticDecoration::setPixmap(const QPixmap &pixmap)
{
	m_pixmap = pixmap;
}

void StaticDecoration::paint(QPainter *painter) const
{
	painter->drawPixmap(10, 10, 16, 16, m_pixmap);
}
