#ifndef GRIDWIDGET_P_H
#define GRIDWIDGET_P_H

#include <QList>

class GridWidget;
class QLabel;

class GridWidgetPrivate
{
	explicit GridWidgetPrivate(GridWidget *parent);

	const int buttonSize;
	const int spacing;
	const int fullSize;

	int actualHeight;

	QLabel *label;
	QList<QWidget *> buttons;

	friend class GridWidget;
};

#endif // GRIDWIDGET_P_H
