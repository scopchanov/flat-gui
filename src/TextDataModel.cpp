#include "TextDataModel.h"
#include "TextDataModel_p.h"
#include "TextEditor.h"
#include "AbstractValidator.h"
#include <QVariant>

/*!
 * \class TextDataModel
 * \inmodule FlatGui
 */

TextDataModel::TextDataModel(QObject *parent) :
	AbstractDataModel(parent),
	m_ptr(new TextDataModelPrivate)
{

}

TextDataModel::~TextDataModel()
{
	delete m_ptr;
}

QVariant TextDataModel::value() const
{
	return m_ptr->text;
}

QString TextDataModel::text() const
{
	return m_ptr->text;
}

QVariant TextDataModel::defaultValue() const
{
	return m_ptr->defaultText;
}

void TextDataModel::setDefaultValue(const QVariant &value)
{
	m_ptr->defaultText = value.toString();
}

AbstractEditor *TextDataModel::editor() const
{
	auto *editor = new TextEditor;

	editor->setText(m_ptr->text);
	editor->setPlaceholderText(m_ptr->placeholderText);

	connect(editor, &TextEditor::editingFinished, this, &TextDataModel::onEditingFinished);

	return editor;
}

void TextDataModel::setPlaceholderText(const QString &text)
{
	m_ptr->placeholderText = text;
}

void TextDataModel::setValue(const QVariant &value)
{
	const QString &str(value.toString());
	const QString &validText(validator() ? validator()->validate(str) : str);

	if (validText == m_ptr->text)
		return;

	if (validText.isEmpty())
		m_ptr->text = m_ptr->defaultText;
	else
		m_ptr->text = validText;

	valueChanged();
}

void TextDataModel::clear()
{
	setValue(m_ptr->defaultText);
}

void TextDataModel::onEditingFinished(bool accepted)
{
	auto *editor = static_cast<TextEditor *>(sender());

	if (accepted)
		setValue(editor->text());

	editor->close();
}

TextDataModelPrivate::TextDataModelPrivate()
{

}
