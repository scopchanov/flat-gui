#ifndef PERSONNAMEVALIDATOR_H
#define PERSONNAMEVALIDATOR_H

#include "AbstractValidator.h"

class PersonNameValidator : public AbstractValidator
{
	Q_OBJECT
public:
	explicit PersonNameValidator(QObject *parent = nullptr);

	QString validate(const QString &text) const override;
};

#endif // PERSONNAMEVALIDATOR_H
