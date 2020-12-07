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

#ifndef MONTHVIEW_H
#define MONTHVIEW_H

#include "components/SMonthPage.h"

class FLATGUISHARED_EXPORT MonthView : public QWidget
{
	Q_OBJECT
public:
	explicit MonthView(QWidget *parent = nullptr);

	QString title() const;
	QDate date() const;
	void setDate(const QDate &date);

protected:
	void resizeEvent(QResizeEvent *) override;

public slots:
	void onDecClicked();
	void onIncClicked();

private:
	void slide(bool left);

	SMonthPage *m_page;
	bool m_transitionInProgress;

private slots:
	void onSlideFinished();

signals:
	void monthChanged(const QString &);
	void dateChanged(const QDate &);
};

#endif // MONTHVIEW_H
