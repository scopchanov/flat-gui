#ifndef PUSHBUTTON_P_H
#define PUSHBUTTON_P_H

#include <QtCore/qglobal.h>

class PushButtonPrivate
{
	explicit PushButtonPrivate();

	QString text;
	qreal highlight;

	friend class PushButton;
};

#endif // PUSHBUTTON_P_H
