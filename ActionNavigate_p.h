#ifndef ACTIONNAVIGATE_P_H
#define ACTIONNAVIGATE_P_H

class SlideView;
class QWidget;

class ActionNavigatePrivate
{
	explicit ActionNavigatePrivate();

	SlideView *view;
	QWidget *page;

	friend class ActionNavigate;
};

#endif // ACTIONNAVIGATE_P_H
