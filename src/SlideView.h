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

#ifndef SLIDEVIEW_H
#define SLIDEVIEW_H

#include "flatgui_global.h"
#include <QWidget>

class SlideViewPrivate;

class FLATGUISHARED_EXPORT SlideView : public QWidget
{
	Q_OBJECT
	Q_PROPERTY(int pageCount READ pageCount NOTIFY pageCountChanged)
	Q_PROPERTY(int currentIndex READ currentIndex WRITE setCurrentIndex
			   NOTIFY currentIndexChanged)
public:
	explicit SlideView(QWidget *parent = nullptr);
	~SlideView();

	void appendPage(QWidget *page);
	int pageCount() const;
	QWidget *currentPage() const;

	int currentIndex() const;
	void setCurrentIndex(int index);

	void removeRemainingPages();

public slots:
	void gotoPreviousPage();
	void gotoFirstPage();
	void gotoNextPage();
	void gotoPage(int index, int duration);

protected:
	void resizeEvent(QResizeEvent *) override;

private:
	SlideViewPrivate *m_ptr;

signals:
	void pageCountChanged();
	void currentIndexChanged();
};

#endif // SLIDEVIEW_H
