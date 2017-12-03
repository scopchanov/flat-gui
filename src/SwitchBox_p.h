#ifndef SWITCHBOX_P_H
#define SWITCHBOX_P_H

#include <QPixmap>

class SwitchBox;

class SwitchBoxPrivate
{
	explicit SwitchBoxPrivate(SwitchBox *parent);

	void createPixmapSlider();

	SwitchBox *p_ptr;

	int offset;
	bool checked;
	bool busy;
	QPixmap pixmap;

	friend class SwitchBox;
};

#endif // SWITCHBOX_P_H
