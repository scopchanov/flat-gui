#include "DateField.h"
#include "DateDataModel.h"
#include <QVariant>

DateField::DateField(QWidget *parent) :
	FancyField(parent)
{
	setDataModel(new DateDataModel);
}

void DateField::setDate(const QDate &date)
{
	dataModel()->setValue(date);
}

void DateField::setDefaultDate(const QDate &date)
{
	dataModel()->setDefaultValue(date);
	dataModel()->setValue(date);
}
