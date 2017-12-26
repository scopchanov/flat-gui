#ifndef PIXMAPBUILDER_P_H
#define PIXMAPBUILDER_P_H

class QPainter;
class QColor;

class PixmapBuilderPrivate
{
public:
	explicit PixmapBuilderPrivate();

	void drawGrid(QPainter *painter, const QColor &color);
	void drawGridSmall(QPainter *painter, const QColor &color);
	void drawGlass(QPainter *painter, const QColor &color);
	void drawCross(QPainter *painter, const QColor &color);
	void drawBack(QPainter *painter, const QColor &color);
	void drawNext(QPainter *painter, const QColor &color);
	void drawHome(QPainter *painter, const QColor &color);
	void drawMenu(QPainter *painter, const QColor &color);
	void drawCheck(QPainter *painter, const QColor &color);
	void drawUp(QPainter *painter, const QColor &color);
	void drawDown(QPainter *painter, const QColor &color);
	void drawSquare(QPainter *painter, const QColor &color);
	void drawSquareSmall(QPainter *painter, const QColor &color);
	void drawInfo(QPainter *painter, const QColor &color);
	void drawWarning(QPainter *painter, const QColor &color);
	void drawError(QPainter *painter, const QColor &color);

	friend class PixmapBuilder;
};

#endif // PIXMAPBUILDER_P_H
