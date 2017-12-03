#ifndef DOUBLEVALIDATOR_H
#define DOUBLEVALIDATOR_H

#include "flatgui_global.h"
#include "AbstractValidator.h"

class DoubleValidatorPrivate;

class FLATGUISHARED_EXPORT DoubleValidator : public AbstractValidator
{
	Q_OBJECT
public:
	explicit DoubleValidator(QObject *parent = nullptr);
	~DoubleValidator();

	void setMinimum(qreal d);
	void setMaximum(qreal d);

	QString validate(const QString &text) const override;

private:
	DoubleValidatorPrivate *m_ptr;
};

#endif // DOUBLEVALIDATOR_H
