#ifndef SPLITVIEW_P_H
#define SPLITVIEW_P_H

class SplitView;
class QWidget;

class SplitViewPrivate
{
	explicit SplitViewPrivate(SplitView *parent);

	void doLayout(int x);

	SplitView *p_ptr;
	QWidget *baseWidget;
	QWidget *sideWidget;
	int splitSide;
	bool busy;
	bool slideIn;

	friend class SplitView;
};

#endif // SPLITVIEW_P_H
