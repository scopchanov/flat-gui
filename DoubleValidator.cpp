#include "DoubleValidator.h"
#include "DoubleValidator_p.h"
#include <QLocale>

DoubleValidator::DoubleValidator(QObject *parent) :
	AbstractValidator(parent),
	m_ptr(new DoubleValidatorPrivate)
{

}

DoubleValidator::~DoubleValidator()
{
	delete m_ptr;
}

void DoubleValidator::setMinimum(qreal d)
{
	m_ptr->min = d;
}

void DoubleValidator::setMaximum(qreal d)
{
	m_ptr->max = d;
}

QString DoubleValidator::validate(const QString &text) const
{
	bool valid = false;
	qreal d = QLocale().toDouble(text, &valid);

	return valid && (d >= m_ptr->min) && (d <= m_ptr->max) ? text : "";
}

DoubleValidatorPrivate::DoubleValidatorPrivate() :
	min(-32767),
	max(32768)
{

}
