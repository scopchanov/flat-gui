#ifndef TEXTDATAMODEL_P_H
#define TEXTDATAMODEL_P_H

#include <QtCore/qglobal.h>

class TextDataModelPrivate
{
	explicit TextDataModelPrivate();

	QString text;
	QString defaultText;
	QString placeholderText;

	friend class TextDataModel;
};

#endif // TEXTDATAMODEL_P_H
