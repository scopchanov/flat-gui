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
