#ifndef ABSTRACTPANEL_H
#define ABSTRACTPANEL_H

#include "flatgui_global.h"
#include <QWidget>

class FLATGUISHARED_EXPORT AbstractPanel : public QWidget
{
	Q_OBJECT
public:
	explicit AbstractPanel(QWidget *parent = nullptr);

	void addWidget(QWidget *widget);
	void addStretch();
	void addSpacing(int n);

private:
	virtual void fitTo(QWidget *);
};

#endif // ABSTRACTPANEL_H
