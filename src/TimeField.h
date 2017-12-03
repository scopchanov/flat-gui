#ifndef TIMEFIELD_H
#define TIMEFIELD_H

#include "FancyField.h"

class FLATGUISHARED_EXPORT TimeField : public FancyField
{
	Q_OBJECT
public:
	explicit TimeField(QWidget *parent = nullptr);

	void setTime(const QTime &time);
	void setDefaultTime(const QTime &time);
};

#endif // TIMEFIELD_H
