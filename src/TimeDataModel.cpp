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
	return m_ptr->time.toString(Qt::DefaultLocaleShortDate);
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
