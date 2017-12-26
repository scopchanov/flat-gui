#include "AbstractButton.h"
#include <QStyle>
#include <QAction>
#include <QActionEvent>
#include <QMouseEvent>

/*!
 * \class AbstractButton
 * \inmodule FlatGui
 * \brief Base class for all buttons.
 */

AbstractButton::AbstractButton(QWidget *parent) :
	QWidget(parent),
	m_pressed(false),
	m_down(false)
{
	setFocusPolicy(Qt::FocusPolicy(style()->styleHint(QStyle::SH_Button_FocusPolicy)));
	setSizePolicy(QSizePolicy(QSizePolicy::Minimum, QSizePolicy::Fixed, QSizePolicy::DefaultType));
	setAttribute(Qt::WA_WState_OwnSizePolicy, false);
	setForegroundRole(QPalette::ButtonText);
	setBackgroundRole(QPalette::Button);
}

bool AbstractButton::event(QEvent *event)
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

void AbstractButton::actionEvent(QActionEvent *event)
{
	QAction *action = event->action();

	if (!action)
		return;

	QWidget::actionEvent(event);

	connect(this, &AbstractButton::clicked, action, &QAction::trigger);
}

void AbstractButton::mousePressEvent(QMouseEvent *event)
{
	if (event->button() != Qt::LeftButton) {
		event->ignore();
		return;
	}

	if (clickArea().contains(event->pos())) {
		setDown(true);
		m_pressed = true;
		repaint();
		event->accept();
	} else {
		event->ignore();
	}
}

void AbstractButton::mouseReleaseEvent(QMouseEvent *event)
{
	m_pressed = false;

	if (event->button() != Qt::LeftButton) {
		event->ignore();
		return;
	}

	if (!m_down) {
		event->ignore();
		return;
	}

	if (clickArea().contains(event->pos())) {
		m_down = false;
		repaint();
		doClick();
		event->accept();
	} else {
		setDown(false);
		event->ignore();
	}
}

void AbstractButton::mouseMoveEvent(QMouseEvent *event)
{
	if (!(event->buttons() & Qt::LeftButton) || !m_pressed) {
		event->ignore();
		return;
	}

	if (clickArea().contains(event->pos()) != m_down) {
		setDown(!m_down);
		repaint();
		event->accept();
	} else if (!clickArea().contains(event->pos())) {
		event->ignore();
	}
}

QRect AbstractButton::clickArea() const
{
	return rect();
}

void AbstractButton::doClick()
{
	clicked();
}

void AbstractButton::setDown(bool down)
{
	m_down = down;
}
