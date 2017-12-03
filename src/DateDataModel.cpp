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
	return QLocale().toString(m_ptr->date, "dd.MM.yyyy");
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
