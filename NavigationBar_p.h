#ifndef NAVIGATIONBAR_P_H
#define NAVIGATIONBAR_P_H

class QString;

class NavigationBarPrivate
{
	explicit NavigationBarPrivate();

	QString title;
	int titleWidth;

	friend class NavigationBar;
};

#endif // NAVIGATIONBAR_P_H
