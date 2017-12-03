#ifndef TOOLBUTTON_P_H
#define TOOLBUTTON_P_H

#include <QtCore/qglobal.h>

class QPixmap;
class QPoint;

class ToolButtonPrivate
{
	explicit ToolButtonPrivate();

	QPixmap pixmap;
	QPoint pixmapOrigin;
	qreal scaleFactor;

	friend class ToolButton;
};

#endif // TOOLBUTTON_P_H
