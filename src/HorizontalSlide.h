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

#include <QObject>

class QLabel;

class HorizontalSlide : public QObject
{
	Q_OBJECT
public:
	explicit HorizontalSlide(QWidget *parent);

	void setCurrentPage(QWidget *currentPage);
	QWidget *nextPage() const;
	void setNextPage(QWidget *nextPage);

public slots:
	void start(bool slideLeft, int speed);

private:
	QWidget *m_parentWidget;
	QWidget *m_currentPage;
	QWidget *m_nextPage;
	QLabel *m_labCurrent;
	QLabel *m_labNext;
	int m_width;
	int m_height;
	bool m_slideLeft;

private slots:
	void onValueChanged(const QVariant &value);
	void onAnimationFinished();

signals:
	void finished();
};

#endif // HORIZONTALSLIDE_H
