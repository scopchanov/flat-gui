#include "ButtonCategory.h"
#include "ButtonCategory_p.h"
#include <QPainter>

/*!
 * \class ButtonCategory::ButtonCategory
 * \inmodule FlatGui
 */

ButtonCategory::ButtonCategory(QWidget *parent) :
	ToolButton(parent),
	m_ptr(new ButtonCategoryPrivate)
{
	setSize(200);
}

/*!
 * \brief ButtonCategory::setSize
 * \reimp
 */

ButtonCategory::~ButtonCategory()
{
	delete m_ptr;
}

void ButtonCategory::setName(const QString &str)
{
	m_ptr->name = str;
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
