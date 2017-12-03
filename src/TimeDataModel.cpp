#include "TimeDataModel.h"
#include "TimeDataModel_p.h"
#include "TimeEditor.h"
#include <QVariant>
#include <QLocale>

/*!
 * \class TimeDataModel
 * \inmodule FlatGui
 */

TimeDataModel::TimeDataModel(QObject *parent) :
	AbstractDataModel(parent),
	m_ptr(new TimeDataModelPrivate)
{

}

TimeDataModel::~TimeDataModel()
{
	delete m_ptr;
}

QVariant TimeDataModel::value() const
{
	return m_ptr->time;
}

QString TimeDataModel::text() const
{
	return QLocale().toString(m_ptr->time, "HH:mm");
}

QVariant TimeDataModel::defaultValue() const
{
	return m_ptr->defaultTime;
}

void TimeDataModel::setDefaultValue(const QVariant &value)
{
	m_ptr->defaultTime = value.toTime();
}

AbstractEditor *TimeDataModel::editor() const
{
	auto *editor = new TimeEditor();

	editor->setTime(m_ptr->time);

	connect(editor, &TimeEditor::editingFinished, this, &TimeDataModel::onEditingFinished);

	return editor;
}

void TimeDataModel::setValue(const QVariant &value)
{
	const QTime &time(value.toTime());

	if (time == m_ptr->time)
		return;

	if (time.isValid())
		m_ptr->time = time;
	else
		m_ptr->time = m_ptr->defaultTime;

	valueChanged();
}

void TimeDataModel::clear()
{
//	m_ptr->text.clear();
	setValue(m_ptr->defaultTime);
}

void TimeDataModel::onEditingFinished(bool accepted)
{
	auto *editor = static_cast<TimeEditor *>(sender());

	if (accepted) {
//		m_ptr->text = editor->text();
		setValue(editor->time());
	}

	editor->close();
}

TimeDataModelPrivate::TimeDataModelPrivate()
{

}
