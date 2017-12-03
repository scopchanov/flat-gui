#ifndef DATEDATAMODEL_P_H
#define DATEDATAMODEL_P_H

#include <QDate>

class DateDataModelPrivate
{
	explicit DateDataModelPrivate();

	QDate date;
	QDate defaultDate;
	QString text;

	friend class DateDataModel;
};

#endif // DATEDATAMODEL_P_H
