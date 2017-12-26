#ifndef FIELD_P_H
#define FIELD_P_H

#include <QtCore/qglobal.h>

class AbstractDataModel;
class AbstractDecoration;
class ToolButton;

class AbstractFieldPrivate {
	explicit AbstractFieldPrivate();

	AbstractDataModel *model;
	AbstractDecoration *decoration;
	ToolButton *btnClear;
	QString text;
	QString placeholderText;
	bool required;
	bool active;

	friend class AbstractField;
};

#endif // FIELD_P_H
