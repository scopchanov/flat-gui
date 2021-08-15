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

#ifndef MONTHPAGE_H
#define MONTHPAGE_H

#include "AbstractButton.h"
#include <QDate>

class FLATGUISHARED_EXPORT MonthPage : public AbstractButton
{
	Q_OBJECT
public:
	explicit MonthPage(QWidget *parent = nullptr);

	QString title() const;
	QDate date() const;
	void setDate(const QDate &date);
	int year() const;
	int month() const;

	void setup(int year, int month);

protected:
	void mousePressEvent(QMouseEvent *event) override;

	QRect clickArea() const override;
	void paintEvent(QPaintEvent *event) override;
	void doClick() override;

private:
	QHash<int, int> m_daysX;
	QHash<int, int> m_daysY;
	QHash<int, int> m_baseLines;
	QDate m_date;
	int m_daysInMonth;
	int m_offset;
	int m_year;
	int m_month;
	int m_day;

private slots:
	void onTimeout();

signals:
	void dateChanged(const QDate &);
};

#endif // MONTHPAGE_H
