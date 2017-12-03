#ifndef GENERICFORM_P_H
#define GENERICFORM_P_H

#include <QList>

class AbstractField;
class QVBoxLayout;

class GenericFormPrivate
{
	explicit GenericFormPrivate();

	QList<AbstractField *> fields;
	QVBoxLayout *layoutBody;

	friend class GenericForm;
};

#endif // GENERICFORM_P_H
