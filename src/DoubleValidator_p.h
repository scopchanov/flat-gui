#ifndef DOUBLEVALIDATOR_P_H
#define DOUBLEVALIDATOR_P_H

#include <QtCore/qglobal.h>

class DoubleValidatorPrivate
{
	explicit DoubleValidatorPrivate();

	qreal min;
	qreal max;

	friend class DoubleValidator;
};

#endif // DOUBLEVALIDATOR_P_H
