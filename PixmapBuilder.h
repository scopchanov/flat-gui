#ifndef PIXMAPBUILDER_H
#define PIXMAPBUILDER_H

#include "flatgui_global.h"

class PixmapBuilderPrivate;
class QPixmap;
class QColor;

class FLATGUISHARED_EXPORT PixmapBuilder
{
public:
	enum ImageType : int {
		Grid = 0,
		GridSmall,
		Glass,
		Cross,
		Back,
		Next,
		Home,
		Menu,
		Check,
		Up,
		Down,
		Square,
		SquareSmall,
		Info,
		Warning,
		Error
	};

	static QPixmap create(int type, const QColor &color, int size = 16);

private:
	explicit PixmapBuilder();
	~PixmapBuilder();

	QPixmap drawPixmap(int type, const QColor &color, int size);

	PixmapBuilderPrivate *m_ptr;
};

#endif // PIXMAPBUILDER_H
