#ifndef ACTIONNAVIGATE_H
#define ACTIONNAVIGATE_H

#include "flatgui_global.h"
#include <QAction>

class ActionNavigatePrivate;
class SlideView;

class FLATGUISHARED_EXPORT ActionNavigate : public QAction
{
	Q_OBJECT
public:
	explicit ActionNavigate(QWidget *parent = nullptr);

	void setView(SlideView *view);
	void setPage(QWidget *page);

private:
	ActionNavigatePrivate *m_ptr;

private slots:
	void onTriggered();
};

#endif // ACTIONNAVIGATE_H
