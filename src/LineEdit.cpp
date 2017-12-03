#include "LineEdit.h"
#include <QKeyEvent>

/*!
 * \class LineEdit
 * \inmodule FlatGui
 */

LineEdit::LineEdit(QWidget *parent) :
	QLineEdit(parent),
	m_rejected(false)
{

}

bool LineEdit::isRejected() const
{
	return m_rejected;
}

void LineEdit::keyPressEvent(QKeyEvent *event)
{
	if (event->key() == Qt::Key_Escape) {
		m_rejected = true;
		editingFinished();
		return;
	}

	QLineEdit::keyPressEvent(event);
}
