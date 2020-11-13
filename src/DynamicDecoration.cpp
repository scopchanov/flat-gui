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
