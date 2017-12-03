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
