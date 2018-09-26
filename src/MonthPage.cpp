/**
MIT License

Copyright (c) 2018 Michael Scopchanov

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

#include "MonthPage.h"
#include <QMouseEvent>
#include <QLocale>
#include <QPainter>
#include <QTimer>

MonthPage::MonthPage(QWidget *parent) :
	AbstractButton(parent),
	m_date(QDate::currentDate()),
	m_daysInMonth(0),
	m_offset(0),
	m_year(0),
	m_month(0),
	m_day(0)
{
	for (int n = 0; n < 5; n++)
		m_baseLines.insert(n, 48*(n + 1) - 1);

	setup(m_date.year(), m_date.month());
	setAttribute(Qt::WA_DeleteOnClose);
}

QString MonthPage::title() const
{
	return QLocale().monthName(m_month).toUpper() + ", " + QString::number(m_year);
}

QDate MonthPage::date() const
{
	return m_date;
}

void MonthPage::setDate(const QDate &date)
{
	if (date.isValid())
		m_date = date;
}

int MonthPage::year() const
{
	return m_year;
}

int MonthPage::month() const
{
	return m_month;
}

void MonthPage::setup(int year, int month)
{
	QDate currentDate(year, month, 1);
	int weekIndex = 0;

	m_daysInMonth = currentDate.daysInMonth();
	m_offset = currentDate.dayOfWeek() - 2;
	m_year = year;
	m_month = month;

	for (int n = 1; n <= m_daysInMonth; n++) {
		int dayOfWeek = QDate(m_year, m_month, n).dayOfWeek();

		m_daysX.insert(n, 48*(dayOfWeek - 1));
		m_daysY.insert(n, 48*weekIndex);

		if (dayOfWeek == 7)
			weekIndex++;
	}
}

void MonthPage::mousePressEvent(QMouseEvent *event)
{
	if (event->button() != Qt::LeftButton) {
		event->ignore();
		return;
	}

	const QPoint &clickPos(event->pos());

	m_day = 7*(clickPos.y()/48) + clickPos.x()/48 - m_offset;

	if ((m_day > 0) && (m_day <= m_daysInMonth) && clickArea().contains(clickPos)) {
		setDown(true);
		m_pressed = true;
		repaint();
		event->accept();
	} else {
		event->ignore();
	}
}

QRect MonthPage::clickArea() const
{
	return QRect(m_daysX.value(m_day), m_daysY.value(m_day), 48, 48);
}

//void MonthPage::mousePressEvent(QMouseEvent *event)
//{
//	bool leftButton = event->button() & Qt::LeftButton;

//	if (leftButton)
//	{
//		m_day = 7*(event->pos().y()/48) + event->pos().x()/48 - m_offset;

//		if ((m_day > 0) && (m_day <= m_daysInMonth))
//		{
//			m_rect = QRect(m_daysX.value(m_day), m_daysY.value(m_day), 48, 48);
//			setDown(true);
//		}
//	}

//	event->setAccepted(leftButton);
//}

void MonthPage::paintEvent(QPaintEvent *event)
{
	const QRect rectDay(0, 0, 48, 48);
	QPainter painter(this);

	painter.setClipping(true);
	painter.setClipRect(event->rect());
	painter.setRenderHint(QPainter::SmoothPixmapTransform);

	painter.fillRect(0, 0, 336, 288, Qt::white);

	painter.setPen(palette().color(QPalette::Light));

	for (int n = 0; n < 5; n++)
		painter.drawLine(9, m_baseLines.value(n), 327, m_baseLines.value(n));

	for (int n = 1; n <= m_daysInMonth; n++) {
		const QPoint topLeft(m_daysX.value(n), m_daysY.value(n));
		bool selected = QDate(m_year, m_month, n) == m_date;

		QPixmap canvas(48, 48);
		QPainter canvasPainter;

		canvas.fill(Qt::transparent);

		canvasPainter.begin(&canvas);
		canvasPainter.setPen(palette().color(selected ? QPalette::HighlightedText : (n + m_offset) % 7 + 1 > 5 ? QPalette::Mid : QPalette::ButtonText));
		canvasPainter.drawText(rectDay, Qt::AlignCenter, QString::number(n));

		painter.translate(topLeft);

		if (selected)
			painter.fillRect(rectDay, palette().color(QPalette::Highlight));

		if (m_down && (rectDay.translated(topLeft) == clickArea())) {
			painter.setOpacity(0.9);
			painter.translate(rectDay.center());
			painter.scale(0.8958, 0.8958);
			painter.translate(-rectDay.center());
		}

		painter.drawPixmap(0, 0, canvas);
		painter.setOpacity(1);
		painter.resetTransform();
	}
}

void MonthPage::doClick()
{
	auto *timer = new QTimer(this);

	m_date = QDate(m_year, m_month, m_day);
	update();

	timer->setSingleShot(true);
	timer->start(150);

	connect(timer, &QTimer::timeout, this, &MonthPage::onTimeout);
}

void MonthPage::onTimeout()
{
	sender()->deleteLater();
	dateChanged(m_date);
}
