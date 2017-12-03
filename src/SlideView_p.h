#ifndef SLIDEVIEW_P_H
#define SLIDEVIEW_P_H

class SlideView;

class SlideViewPrivate
{
	explicit SlideViewPrivate(SlideView *parent);

	void slideToPage(int n, int speed);

	SlideView *p_ptr;

	QWidgetList pages;
	int currentIndex;
	int nextIndex;
	bool busy;

	friend class SlideView;
};

#endif // SLIDEVIEW_P_H
