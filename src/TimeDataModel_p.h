#ifndef TIMEDATAMODEL_P_H
#define TIMEDATAMODEL_P_H

#include <QTime>

class TimeDataModelPrivate
{
	explicit TimeDataModelPrivate();

	QTime time;
	QTime defaultTime;

	friend class TimeDataModel;
};

#endif // TIMEDATAMODEL_P_H
