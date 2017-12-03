#include "SidePanel.h"
#include <QPainter>
#include <QPaintEvent>
#include <QVBoxLayout>

/*!
 * \class SidePanel
 * \inmodule FlatGui
 */

SidePanel::SidePanel(QWidget *parent) :
	AbstractPanel(parent)
{
	auto *layoutMain = new QVBoxLayout(this);

	layoutMain->setContentsMargins(1, 0, 0, 0);
	layoutMain->setSpacing(0);
	layoutMain->setSizeConstraint(QLayout::SetMinimumSize);

	setBackgroundRole(QPalette::Button);
	setAutoFillBackground(true);
	setMinimumWidth(100);
}

void SidePanel::paintEvent(QPaintEvent *event)
{
	QPainter painter(this);

	painter.setClipping(true);
	painter.setClipRect(event->rect());
	painter.setPen(palette().color(QPalette::Midlight));
	painter.drawLine(0, 0, 0, height());
}

void SidePanel::fitTo(QWidget *widget)
{
	int w = widget->minimumWidth();

	if (w > width())
		setMinimumWidth(w);
}
