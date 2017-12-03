#ifndef NAVIGATIONBAR_H
#define NAVIGATIONBAR_H

#include "flatgui_global.h"
#include "AbstractPanel.h"

class NavigationBarPrivate;

class FLATGUISHARED_EXPORT NavigationBar : public AbstractPanel
{
	Q_OBJECT
public:
	explicit NavigationBar(QWidget *parent = nullptr);
	~NavigationBar();

public slots:
	void setTitle(const QString &title);

protected:
	void paintEvent(QPaintEvent *event) override;

private:
	NavigationBarPrivate *m_ptr;
};

#endif // NAVIGATIONBAR_H
