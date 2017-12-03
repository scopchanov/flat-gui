#ifndef ABSTRACTDATAMODEL_P_H
#define ABSTRACTDATAMODEL_P_H

#include <QtCore/qglobal.h>

class AbstractValidator;

class AbstractDataModelPrivate
{
	explicit AbstractDataModelPrivate();

	AbstractValidator *validator;

	friend class AbstractDataModel;
};

#endif // ABSTRACTDATAMODEL_P_H
