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

#include "SAbstractButton.h"
#include "SAbstractButton_p.h"
#include <QStyle>
#include <QAction>
#include <QActionEvent>
#include <QMouseEvent>

/*!
	\class SAbstractButton
	\inmodule CDK
	\ingroup Buttons
	\brief Base class for all buttons.
 */

SAbstractButton::SAbstractButton(QWidget *parent) :
	QWidget(parent),
	m_ptr(new SAbstractButtonPrivate(this))
{
	setFocusPolicy(Qt::FocusPolicy(style()
								   ->styleHint(QStyle::SH_Button_FocusPolicy)));
	setSizePolicy(QSizePolicy(QSizePolicy::Minimum, QSizePolicy::Fixed,
							  QSizePolicy::DefaultType));
	setAttribute(Qt::WA_WState_OwnSizePolicy, false);
	setForegroundRole(QPalette::ButtonText);
	setBackgroundRole(QPalette::Button);
}

SAbstractButton::~SAbstractButton()
{
	delete m_ptr;
}

bool SAbstractButton::isPressed() const
{
	return m_ptr->pressed;
}


bool SAbstractButton::isDown() const
{
	return m_ptr->down;
}

bool SAbstractButton::event(QEvent *event)
{
	if (!isEnabled()) {
		switch(event->type()) {
		case QEvent::TabletPress:
		case QEvent::TabletRelease:
		case QEvent::TabletMove:
		case QEvent::MouseButtonPress:
		case QEvent::MouseButtonRelease:
		case QEvent::MouseButtonDblClick:
		case QEvent::MouseMove:
		case QEvent::HoverMove:
		case QEvent::HoverEnter:
		case QEvent::HoverLeave:
		case QEvent::ContextMenu:
			return true;
		default:
			break;
		}
	}

	return QWidget::event(event);
}

void SAbstractButton::setPressed(bool pressed)
{
	if (m_ptr->pressed == pressed)
		return;

	m_ptr->pressed = pressed;
}

void SAbstractButton::setDown(bool down)
{
	if (m_ptr->down == down)
		return;

	m_ptr->down = down;
}

void SAbstractButton::actionEvent(QActionEvent *event)
{
	QAction *action = event->action();

	if (!action)
		return;

	QWidget::actionEvent(event);

	connect(this, &SAbstractButton::clicked, action, &QAction::trigger);
}

void SAbstractButton::mousePressEvent(QMouseEvent *event)
{
	if (event->button() != Qt::LeftButton) {
		event->ignore();
		return;
	}

	if (clickArea().contains(event->pos())) {
		setDown(true);
		m_ptr->pressed = true;
		repaint();
		event->accept();
	} else {
		event->ignore();
	}
}

void SAbstractButton::mouseReleaseEvent(QMouseEvent *event)
{
	m_ptr->pressed = false;

	if (event->button() != Qt::LeftButton) {
		event->ignore();
		return;
	}

	if (!m_ptr->down) {
		event->ignore();
		return;
	}

	if (clickArea().contains(event->pos())) {
		m_ptr->down = false;
		repaint();
		doClick();
		event->accept();
	} else {
		setDown(false);
		event->ignore();
	}
}

void SAbstractButton::mouseMoveEvent(QMouseEvent *event)
{
	if (!(event->buttons() & Qt::LeftButton) || !m_ptr->pressed) {
		event->ignore();
		return;
	}

	if (clickArea().contains(event->pos()) != m_ptr->down) {
		setDown(!m_ptr->down);
		repaint();
		event->accept();
	} else if (!clickArea().contains(event->pos())) {
		event->ignore();
	}
}

QRect SAbstractButton::clickArea() const
{
	return rect();
}

void SAbstractButton::doClick()
{
	emit clicked();
}

SAbstractButtonPrivate::SAbstractButtonPrivate(SAbstractButton *parent) :
	p_ptr(parent),
	pressed(false),
	down(false)
{

}
