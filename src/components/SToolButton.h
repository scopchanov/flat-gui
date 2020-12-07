/**
MIT License

Copyright (c) 2020 Michael Scopchanov

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

#ifndef STOOLBUTTON_H
#define STOOLBUTTON_H

#include "cdk/SAbstractButton.h"

class SToolButtonPrivate;

class FLATGUISHARED_EXPORT SToolButton : public SAbstractButton
{
	Q_OBJECT
public:
	explicit SToolButton(QWidget *parent = nullptr);
	~SToolButton();

	void setPixmap(const QPixmap &pixmap);
	virtual void setSize(int n);

protected:
	void paintEvent(QPaintEvent *event) override final;

	virtual void paint(QPainter *painter);
	void setPixmapOrigin(const QPoint &p);
	void setScaleFactor(qreal d);

private:
	SToolButtonPrivate *m_ptr;
};

#endif // STOOLBUTTON_H
