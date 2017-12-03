#ifndef SPLITVIEW_P_H
#define SPLITVIEW_P_H

class SplitView;
class QWidget;

class SplitViewPrivate
{
	explicit SplitViewPrivate(SplitView *parent);

	void setHorizontalSplit(int x);

	SplitView *p_ptr;
	QWidget *baseWidget;
	QWidget *sideWidget;
	bool busy;
	bool slideIn;

	friend class SplitView;
};

#endif // SPLITVIEW_P_H
