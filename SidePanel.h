#ifndef SIDEPANEL_H
#define SIDEPANEL_H

#include "AbstractPanel.h"

class FLATGUISHARED_EXPORT SidePanel : public AbstractPanel
{
	Q_OBJECT
public:
	explicit SidePanel(QWidget *parent = nullptr);

protected:
	void paintEvent(QPaintEvent *event) override;
	void fitTo(QWidget *widget) override;
};

#endif // SIDEPANEL_H
