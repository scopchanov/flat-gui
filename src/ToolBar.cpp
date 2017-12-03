#include "ToolBar.h"
#include <QHBoxLayout>

/*!
 * \class ToolBar
 * \inmodule FlatGui
 */

ToolBar::ToolBar(QWidget *parent) :
	AbstractPanel(parent)
{
	auto *layoutMain(new QHBoxLayout(this));

	layoutMain->setSizeConstraint(QLayout::SetMinimumSize);
	layoutMain->setContentsMargins(0, 0, 0, 0);
	layoutMain->setSpacing(0);

	setBackgroundRole(QPalette::Light);
	setAutoFillBackground(true);
}
