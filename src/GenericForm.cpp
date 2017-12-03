#include "GenericForm.h"
#include "GenericForm_p.h"
#include "AbstractField.h"
#include "DynamicDecoration.h"
#include <QJsonObject>
#include <QHBoxLayout>
#include <QLabel>
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
	auto *label = new QLabel(tr("The fields marked with %1 need to be filled out."
								" The rest of the fields are either optional or already contain information.")
							 .arg("&nbsp;<img src=':/pix/images/icons/8/grip-color-small.png' />&nbsp;"), this);
	QFont f(font());

	f.setPointSize(10);

	label->setFont(f);
	label->setWordWrap(true);
	label->setForegroundRole(QPalette::Text);

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

//	AbstractFormField *field = table ? (AbstractFormField *)(new TableField(this)) : (AbstractFormField *)(new TextField(this));

////	if (table) { field = new TableField(this); } else { field = new TextField(this); }

//	field->setObjectName(name);
//	field->setRequired(required);
//	field->setPlaceholderText(title);
//	if (table) { static_cast<TableField *>(field)->setTable(table); }

//	m_fields.append(field);
//	m_layoutBody->addWidget(field);

//	connect(field, &AbstractFormField::contentChanged, this, &FormWidget::contentChanged);
//	connect(m_actClear, &QAction::triggered, field, &AbstractFormField::clear);
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
