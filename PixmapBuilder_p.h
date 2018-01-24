/**
MIT License

Copyright (c) 2018 Michael Scopchanov

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

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
