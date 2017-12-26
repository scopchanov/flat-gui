#include "ValidatorFactory.h"
#include "PersonNameValidator.h"

/*!
 * \class ValidatorFactory
 * \inmodule FlatGui
 */

AbstractValidator *ValidatorFactory::create(const ValidatorType &type)
{
	switch (type) {
	case ValidatorType::PersonNameValidator:
		return new PersonNameValidator;
//	case ValidatorType::DateEditor:
//		return new DateEditor(field);
	default:
		return nullptr;
	}
}
