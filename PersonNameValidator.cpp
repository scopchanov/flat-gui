#include "PersonNameValidator.h"

PersonNameValidator::PersonNameValidator(QObject *parent) :
	AbstractValidator(parent)
{

}

QString PersonNameValidator::validate(const QString &text) const
{
	return QString(text).remove(QRegExp("[^a-zA-Z'-\\s]"));
}
