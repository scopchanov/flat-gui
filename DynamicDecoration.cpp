#include "DynamicDecoration.h"
#include <QPainter>

/*!
 * \class DynamicDecoration
 * \inmodule FlatGui
 */

DynamicDecoration::DynamicDecoration(QObject *parent) :
	AbstractDecoration(parent),
	m_on(false)
{

}

void DynamicDecoration::setPixmapOn(const QPixmap &pixmapValid)
{
	m_pixmapOn = pixmapValid;
}

void DynamicDecoration::setPixmapOff(const QPixmap &pixmapInvalid)
{
	m_pixmapOff = pixmapInvalid;
}

void DynamicDecoration::paint(QPainter *painter) const
{
	painter->drawPixmap(10, 10, 16, 16, m_on ? m_pixmapOn : m_pixmapOff);
}

void DynamicDecoration::setState(bool on)
{
	m_on = on;
}
