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

#include "ButtonCategory.h"
#include "ButtonCategory_p.h"
#include <QPainter>

/*!
 * \class ButtonCategory
 * \inmodule FlatGui
 */

ButtonCategory::ButtonCategory(QWidget *parent) :
	ToolButton(parent),
	m_ptr(new ButtonCategoryPrivate)
{
	setSize(200);
}

ButtonCategory::~ButtonCategory()
{
	delete m_ptr;
}

void ButtonCategory::setName(const QString &str)
{

	m_ptr->name = str.left(1).toUpper() + str.mid(1, str.length() - 1);
}

void ButtonCategory::setDescription(const QString &str)
{
	m_ptr->description = str;
}

void ButtonCategory::setSize(int n)
{
	setPixmapOrigin(QPoint(68, 18));
	setScaleFactor(0.97);

	resize(n, n);
}

/*!
 * \brief ButtonCategory::paint
 * \reimp
 */

void ButtonCategory::paint(QPainter *painter)
{
	QFont fntName(font());

	fntName.setBold(true);

	// Draw background
	painter->fillRect(rect(), palette().color(QPalette::Button));

	// Draw name
	painter->setFont(fntName);
	painter->drawText(rect(), Qt::AlignCenter | Qt::TextSingleLine, m_ptr->name);

	// Draw description
	painter->setFont(font());
	painter->setPen(palette().color(QPalette::Text));
	painter->drawText(rect().adjusted(12, 120, -12, -12), Qt::AlignHCenter | Qt::AlignTop | Qt::TextWordWrap, m_ptr->description);

	// Draw border
	painter->setPen(palette().color(QPalette::Midlight));
	painter->drawRect(rect().adjusted(0, 0, -1, -1));

	ToolButton::paint(painter);
}

ButtonCategoryPrivate::ButtonCategoryPrivate()
{

}
