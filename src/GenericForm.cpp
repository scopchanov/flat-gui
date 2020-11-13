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

#include "GenericForm.h"
#include "GenericForm_p.h"
#include "AbstractField.h"
#include "DynamicDecoration.h"
#include "PixmapBuilder.h"
#include <QJsonObject>
#include <QHBoxLayout>
#include <QLabel>
#include <QBuffer>
#include <QDateTime>

/*!
 * \class GenericForm
 * \inmodule FlatGui
 */

GenericForm::GenericForm(QWidget *parent) :
	QWidget(parent),
	m_ptr(new GenericFormPrivate)
{
	auto *layoutMain = new QHBoxLayout(this);
	auto *label = new QLabel(this);
	QFont f(font());
	QByteArray ba;
	QBuffer buffer(&ba);

	f.setPointSize(10);

	PixmapBuilder::create(PixmapBuilder::GridSmall,
						  palette().color(QPalette::Highlight), 8)
			.save(&buffer, "PNG");

	label->setFont(f);
	label->setWordWrap(true);
	label->setForegroundRole(QPalette::Text);
	label->setText(tr("The fields marked with %1 need to be filled out. "
					  "The rest of the fields are either optional or"
					  " already contain information.")
				   .arg(QString("&nbsp;<img src='data:image/png;base64,"
								+ ba.toBase64() + "' />&nbsp;")));

	m_ptr->layoutBody->addWidget(label);
	m_ptr->layoutBody->addStretch();
	m_ptr->layoutBody->setContentsMargins(0, 0, 0, 0);
	m_ptr->layoutBody->setSpacing(9);

	layoutMain->addStretch();
	layoutMain->addLayout(m_ptr->layoutBody);
	layoutMain->addStretch();
	layoutMain->setSpacing(0);
	layoutMain->setStretch(0, 20);
	layoutMain->setStretch(1, 80);
	layoutMain->setStretch(2, 20);
	layoutMain->setContentsMargins(24, 24, 24, 24);
	layoutMain->setSpacing(0);

	setFocusPolicy(Qt::StrongFocus);
}

GenericForm::~GenericForm()
{
	delete m_ptr;
}

void GenericForm::addField(AbstractField *field)
{
	if (!field)
		return;

	field->setParent(this);

	m_ptr->layoutBody->insertWidget(m_ptr->layoutBody->count() - 1, field);
	m_ptr->fields.append(field);
}

bool GenericForm::isEmpty() const
{
	foreach (AbstractField *field, m_ptr->fields)
		if (!field->isEmpty())
			return false;

	return true;
}

bool GenericForm::isValid() const
{
	foreach (AbstractField *field, m_ptr->fields)
		if (!field->isValid())
			return false;

	return true;
}

QJsonObject GenericForm::content() const
{
	QJsonObject entry;

	foreach (AbstractField *field, m_ptr->fields)
		if (!field->isEmpty())
			entry[field->objectName()] = QJsonValue::fromVariant(field->value());

	entry["Timestamp"] = QDateTime::currentDateTime().toString(Qt::ISODate);

	return entry;
}

void GenericForm::clear() const
{
	foreach (AbstractField *field, m_ptr->fields)
		field->clear();
}

GenericFormPrivate::GenericFormPrivate() :
	layoutBody(new QVBoxLayout())
{

}
