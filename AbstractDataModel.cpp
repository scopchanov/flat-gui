#include "AbstractDataModel.h"
#include "AbstractDataModel_p.h"
#include "AbstractValidator.h"

/*!
 * \class AbstractDataModel
 * \inmodule FlatGui
 * \brief Base class for all data models.
 */

AbstractDataModel::AbstractDataModel(QObject *parent) :
	QObject(parent),
	m_ptr(new AbstractDataModelPrivate)
{

}

AbstractDataModel::~AbstractDataModel()
{
	delete m_ptr;
}

void AbstractDataModel::setValidator(AbstractValidator *validator)
{
	if (!validator)
		return;

	validator->setParent(this);
	m_ptr->validator = validator;
}

AbstractValidator *AbstractDataModel::validator() const
{
	return m_ptr->validator;
}

AbstractDataModelPrivate::AbstractDataModelPrivate() :
	validator(nullptr)
{

}
