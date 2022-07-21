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
	Q_PROPERTY(QWidget *baseWidget READ baseWidget WRITE setBaseWidget
			   NOTIFY baseWidgetChanged)
	Q_PROPERTY(QWidget *sideWidget READ sideWidget WRITE setSideWidget
			   NOTIFY sideWidgetChanged)
	Q_PROPERTY(SideType splitSide READ splitSide WRITE setSplitSide
			   NOTIFY splitSideChanged)
	Q_PROPERTY(int splitDuration READ splitDuration WRITE setSplitDuration
			   NOTIFY splitDurationChanged)
	Q_PROPERTY(StateType sideWidgetState READ sideWidgetState
			   NOTIFY sideWidgetStateChanged)
public:
	enum SideType : int {
		ST_Left = 0,
		ST_Right
	};

	enum StateType : int {
		ST_Closed = 0,
		ST_Open
	};

	explicit SplitView(QWidget *parent = nullptr);
	~SplitView();

	QWidget *baseWidget() const;
	void setBaseWidget(QWidget *widget);
	QWidget *sideWidget() const;
	void setSideWidget(QWidget *widget);
	SideType splitSide() const;
	void setSplitSide(SideType side);
	int splitDuration() const;
	void setSplitDuration(int duration);
	StateType sideWidgetState() const;

	void openSideWidget();
	void closeSideWidget();

public slots:
	void toggleSideWidget();

protected:
	void resizeEvent(QResizeEvent *) override;

private:
	SplitViewPrivate *m_ptr;

signals:
	void baseWidgetChanged();
	void sideWidgetChanged();
	void splitSideChanged();
	void splitDurationChanged();
	void sideWidgetStateChanged();
};

#endif // SPLITVIEW_H
