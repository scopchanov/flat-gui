#ifndef DATEFIELD_H
#define DATEFIELD_H

#include "FancyField.h"

class FLATGUISHARED_EXPORT DateField : public FancyField
{
	Q_OBJECT
public:
	explicit DateField(QWidget *parent = nullptr);

	void setDate(const QDate &date);
	void setDefaultDate(const QDate &date);
};

#endif // DATEFIELD_H
