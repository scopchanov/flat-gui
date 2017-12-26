#ifndef BUTTONCATEGORY_P_H
#define BUTTONCATEGORY_P_H

#include <QtCore/qglobal.h>

class ButtonCategoryPrivate
{
	explicit ButtonCategoryPrivate();

	QString name;
	QString description;

	friend class ButtonCategory;
};

#endif // BUTTONCATEGORY_P_H
