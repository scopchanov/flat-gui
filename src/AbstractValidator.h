#ifndef ABSTRACTVALIDATOR_H
#define ABSTRACTVALIDATOR_H

#include <QObject>

class AbstractValidator : public QObject
{
	Q_OBJECT
public:
	explicit AbstractValidator(QObject *parent = nullptr);

	virtual QString validate(const QString &text) const = 0;
};

#endif // ABSTRACTVALIDATOR_H
