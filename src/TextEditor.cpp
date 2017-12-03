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
