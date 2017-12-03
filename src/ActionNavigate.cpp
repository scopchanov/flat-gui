#include "ActionNavigate.h"
#include "ActionNavigate_p.h"
#include "SlideView.h"

/*!
 * \class ActionNavigate
 * \inmodule FlatGui
 */

ActionNavigate::ActionNavigate(QWidget *parent) :
	QAction(parent),
	m_ptr(new ActionNavigatePrivate)
{
	connect(this, &ActionNavigate::triggered, this, &ActionNavigate::onTriggered);
}

void ActionNavigate::setView(SlideView *view)
{
	m_ptr->view = view;
}

void ActionNavigate::setPage(QWidget *page)
{
	m_ptr->page = page;
}

void ActionNavigate::onTriggered()
{
	if (!m_ptr->view || !m_ptr->page)
		return;

	m_ptr->view->addPage(m_ptr->page);
}

ActionNavigatePrivate::ActionNavigatePrivate() :
	view(nullptr),
	page(nullptr)
{

}
