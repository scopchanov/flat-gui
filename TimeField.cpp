#include "TimeField.h"
#include "TimeDataModel.h"
#include <QVariant>

TimeField::TimeField(QWidget *parent) :
	FancyField(parent)
{
	setDataModel(new TimeDataModel);
}

void TimeField::setTime(const QTime &time)
{
	dataModel()->setValue(time);
}

void TimeField::setDefaultTime(const QTime &time)
{
	dataModel()->setDefaultValue(time);
	dataModel()->setValue(time);
}
