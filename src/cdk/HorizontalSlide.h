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

#ifndef HORIZONTALSLIDE_H
#define HORIZONTALSLIDE_H

#include "flatgui_global.h"
#include <QWidget>

class QLabel;
class HorizontalSlidePrivate;

class FLATGUISHARED_EXPORT HorizontalSlide : public QWidget
{
	Q_OBJECT
	Q_PROPERTY(QWidget *currentPage READ currentPage WRITE setCurrentPage
			   NOTIFY currentPageChanged)
	Q_PROPERTY(QWidget *nextPage READ nextPage WRITE setNextPage
			   NOTIFY nextPageChanged)
	Q_PROPERTY(SlideDirection direction READ direction WRITE setDirection
			   NOTIFY directionChanged)
	Q_PROPERTY(int duration READ duration WRITE setDuration
			   NOTIFY durationChanged)
	Q_PROPERTY(bool inProgress READ inProgress NOTIFY inProgressChanged)
public:
	enum SlideDirection : int {
		SD_SlideLeft = 0,
		SD_SlideRight
	};

	explicit HorizontalSlide(QWidget *parent = nullptr);
	~HorizontalSlide();

	QWidget *currentPage() const;
	void setCurrentPage(QWidget *page);
	QWidget *nextPage() const;
	void setNextPage(QWidget *page);
	SlideDirection direction() const;
	void setDirection(SlideDirection direction);
	int duration() const;
	void setDuration(int duration);
	bool inProgress() const;

public slots:
	void start();

private:
	HorizontalSlidePrivate *m_ptr;

signals:
	void currentPageChanged();
	void nextPageChanged();
	void directionChanged();
	void durationChanged();
	void inProgressChanged();

	friend class HorizontalSlidePrivate;
};

#endif // HORIZONTALSLIDE_H
