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

#include "DateDataModel.h"
#include "DateDataModel_p.h"
#include "DateEditor.h"
#include <QVariant>
#include <QLocale>

/*!
 * \class DateDataModel
 * \inmodule FlatGui
 */

DateDataModel::DateDataModel(QObject *parent) :
	AbstractDataModel(parent),
	m_ptr(new DateDataModelPrivate)
{

}

DateDataModel::~DateDataModel()
{
	delete m_ptr;
}

QVariant DateDataModel::value() const
{
	return m_ptr->date;
}

QString DateDataModel::text() const
{
	return m_ptr->date.toString(Qt::DefaultLocaleShortDate);
}

QVariant DateDataModel::defaultValue() const
{
	return m_ptr->defaultDate;
}

void DateDataModel::setDefaultValue(const QVariant &value)
{
	m_ptr->defaultDate = value.toDate();
}

AbstractEditor *DateDataModel::editor() const
{
	auto *editor = new DateEditor();

	editor->setDate(m_ptr->date);

	connect(editor, &DateEditor::editingFinished, this, &DateDataModel::onEditingFinished);

	return editor;
}

void DateDataModel::setValue(const QVariant &value)
{
	const QDate &date(value.toDate());

	if (date == m_ptr->date)
		return;

	if (date.isValid())
		m_ptr->date = date;
	else
		m_ptr->date = m_ptr->defaultDate;

	valueChanged();
}

void DateDataModel::clear()
{
	m_ptr->text.clear();
	setValue(m_ptr->defaultDate);
}

void DateDataModel::onEditingFinished(bool accepted)
{
	auto *editor = static_cast<DateEditor *>(sender());

	if (accepted) {
//		m_ptr->text = editor->text();
		setValue(editor->date());
	}

	editor->close();
}

DateDataModelPrivate::DateDataModelPrivate()
{

}
