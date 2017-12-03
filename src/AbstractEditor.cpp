#include "AbstractEditor.h"
#include "AbstractEditor_p.h"
#include <QPropertyAnimation>

/*!
 * \class AbstractEditor
 * \inmodule FlatGui
 * \brief Base class for all editors.
 */

AbstractEditor::AbstractEditor(QWidget *parent, Qt::WindowFlags f) :
	QWidget(parent, f),
	m_ptr(new AbstractEditorPrivate)
{
	setAttribute(Qt::WA_DeleteOnClose);
	setFocusPolicy(Qt::StrongFocus);
}

AbstractEditor::~AbstractEditor()
{
	delete m_ptr;
}

AbstractField *AbstractEditor::field() const
{
	return m_ptr->field;
}

void AbstractEditor::setField(AbstractField *field)
{
	m_ptr->field = field;

	setup();
}

void AbstractEditor::showEvent(QShowEvent *)
{
	auto* animation = new QPropertyAnimation(this, "windowOpacity", this);

	animation->setStartValue(0.0);
	animation->setEndValue(1.0);
	animation->setDuration(100);
	animation->start(QPropertyAnimation::DeleteWhenStopped);
}

void AbstractEditor::setup()
{

}


AbstractEditorPrivate::AbstractEditorPrivate() :
	field(nullptr)
{

}
