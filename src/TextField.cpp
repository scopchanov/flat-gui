#include "TextField.h"
#include "TextDataModel.h"
#include <QVariant>

TextField::TextField(QWidget *parent) :
	FancyField(parent)
{
	setDataModel(new TextDataModel);
}

void TextField::setText(const QString &text)
{
	dataModel()->setValue(text);
}

void TextField::setPlaceholderText(const QString &text)
{
	FancyField::setPlaceholderText(text);

	static_cast<TextDataModel *>(dataModel())->setPlaceholderText(text);
}

void TextField::setDefaultText(const QString &text)
{
	dataModel()->setDefaultValue(text);
	dataModel()->setValue(text);
}
