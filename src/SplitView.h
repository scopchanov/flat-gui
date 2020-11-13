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

#ifndef SPLITVIEW_H
#define SPLITVIEW_H

#include "flatgui_global.h"
#include <QWidget>

class SplitViewPrivate;

class FLATGUISHARED_EXPORT SplitView : public QWidget
{
	Q_OBJECT
public:
	enum SideType : int {
		ST_Left,
		ST_Right
	};

	explicit SplitView(QWidget *parent = nullptr);
	~SplitView();

	void setBaseWidget(QWidget *widget);
	void setSideWidget(QWidget *widget, bool hidden = true);
	SideType splitSide() const;
	void setSplitSide(SideType sd);

public slots:
	void toggleSideWidget();

protected:
	void resizeEvent(QResizeEvent *) override;

private:
	SplitViewPrivate *m_ptr;

private slots:
	void onValueChanged(const QVariant &value);
	void onAnimationFinished();

signals:
	void toggled(bool isOpen);
};

#endif // SPLITVIEW_H
