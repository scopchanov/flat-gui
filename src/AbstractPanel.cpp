#include "AbstractPanel.h"
#include <QBoxLayout>

/*!
 * \class AbstractPanel
 * \inmodule FlatGui
 * \brief Base class for all panels.
 */

AbstractPanel::AbstractPanel(QWidget *parent) :
	QWidget(parent)
{
	setFocusPolicy(Qt::StrongFocus);
}

void AbstractPanel::addWidget(QWidget *widget)
{
	if (!widget)
		return;

	widget->setParent(this);
	layout()->addWidget(widget);

	fitTo(widget);
}

void AbstractPanel::addStretch()
{
	static_cast<QBoxLayout *>(layout())->addStretch();
}

void AbstractPanel::addSpacing(int n)
{
	static_cast<QBoxLayout *>(layout())->addSpacing(n);
}

void AbstractPanel::fitTo(QWidget *)
{

}
