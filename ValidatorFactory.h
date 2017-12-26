#ifndef VALIDATORFACTORY_H
#define VALIDATORFACTORY_H

#include "flatgui_global.h"

class AbstractValidator;

enum class ValidatorType : int {
	NoValidator = 0,
	PersonNameValidator
};

struct FLATGUISHARED_EXPORT ValidatorFactory
{
	static AbstractValidator *create(const ValidatorType &type);
};

#endif // VALIDATORFACTORY_H
