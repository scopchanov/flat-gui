#include "NavigationBar.h"
#include "NavigationBar_p.h"
#include <QHBoxLayout>
#include <QPaintEvent>
#include <QPainter>

/*!
 * \class NavigationBar
 * \inmodule FlatGui
 */

NavigationBar::NavigationBar(QWidget *parent) :
	AbstractPanel(parent),
	m_ptr(new NavigationBarPrivate)
{
	QHBoxLayout *layoutMain = new QHBoxLayout(this);
	QFont f{QFont()};

	layoutMain->setSizeConstraint(QLayout::SetMinimumSize);
	layoutMain->setContentsMargins(0, 0, 0, 0);
	layoutMain->setSpacing(0);

	f.setBold(true);

	setFixedHeight(48);
	setFont(f);
	setBackgroundRole(QPalette::Dark);
	setAutoFillBackground(true);
}

NavigationBar::~NavigationBar()
{
	delete m_ptr;
}

void NavigationBar::setTitle(const QString &title)
{
	m_ptr->title = title.toUpper();
	m_ptr->titleWidth = fontMetrics().width(m_ptr->title);

	update();
}

void NavigationBar::paintEvent(QPaintEvent *event)
{
	QPainter painter(this);
	const int w = width(), minWidth = 192 + m_ptr->titleWidth;

	painter.setClipping(true);
	painter.setClipRect(event->rect());

	painter.setPen(palette().color(QPalette::HighlightedText));
	painter.setOpacity(w <= minWidth ? 0.0 : w >= minWidth + 48 ? 1.0 : (w - minWidth)/48.0);
	painter.drawText(QRect(0, 0, w, 48), Qt::AlignCenter, m_ptr->title);
}

NavigationBarPrivate::NavigationBarPrivate() :
	titleWidth(0)
{

}
