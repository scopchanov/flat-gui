/**
MIT License

Copyright (c) 2018 Michael Scopchanov

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

#include "TextEditor.h"
#include "LineEdit.h"
#include <QVBoxLayout>
#include <AbstractField.h>

/*!
 * \class TextEditor
 * \inmodule FlatGui
 */

TextEditor::TextEditor(QWidget *parent) :
	AbstractEditor(parent),
	m_lineEdit(new LineEdit(this))
{
	auto *layoutMain(new QVBoxLayout(this));

	m_lineEdit->setFixedHeight(32);
	m_lineEdit->setStyleSheet(".LineEdit {"
							"	background-color: palette(button);"
							"	color: palette(window-text);"
							"	border: 0;"
							"}");

	layoutMain->addWidget(m_lineEdit);
	layoutMain->setContentsMargins(0, 0, 0, 0);
	layoutMain->setSpacing(0);

	setFocusProxy(m_lineEdit);
	setBackgroundRole(QPalette::Highlight);
	setFixedHeight(32);

	connect(m_lineEdit, &LineEdit::editingFinished, this, &TextEditor::onEditingFinished);
}

QString TextEditor::text() const
{
	return m_lineEdit->text();
}

void TextEditor::setText(const QString &str)
{
	m_lineEdit->setText(str);
	m_lineEdit->selectAll();
}

void TextEditor::setPlaceholderText(const QString &str)
{
	m_lineEdit->setPlaceholderText(str);
}

void TextEditor::reposition()
{
	setGeometry(field()->textArea());
}

void TextEditor::setup()
{
	setParent(field());
}

void TextEditor::onEditingFinished()
{
	m_lineEdit->blockSignals(true); // this line is needed to prevent the textChanged() from being emitted twice

	editingFinished(!m_lineEdit->isRejected());
}
