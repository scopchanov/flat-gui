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

#ifndef SPLITVIEW_P_H
#define SPLITVIEW_P_H

#include <QtCore/qglobal.h>

class SplitView;
class QWidget;

class SplitViewPrivate
{
	Q_DISABLE_COPY(SplitViewPrivate)

	explicit SplitViewPrivate(SplitView *parent);

	void startTransition();
	void setSideWidgetState(int value);
	void resizeWidgets();
	void layoutWidgets(int x);

	SplitView *p_ptr;
	QWidget *baseWidget;
	QWidget *sideWidget;
	int splitSide;
	int splitDuration;
	int sideWidgetState;
	bool inProgress;

	friend class SplitView;
};

#endif // SPLITVIEW_P_H
