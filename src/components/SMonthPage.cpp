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

#include "SMonthPage.h"
#include "SMonthPage_p.h"
#include <QMouseEvent>
#include <QLocale>
#include <QPainter>
#include <QTimer>

SMonthPage::SMonthPage(QWidget *parent) :
	SAbstractButton(parent),
	m_ptr(new SMonthPagePrivate())
{
	for (int n = 0; n < 5; n++)
		m_ptr->baseLines.insert(n, 48*(n + 1) - 1);

	setup(m_ptr->date.year(), m_ptr->date.month());
	setAttribute(Qt::WA_DeleteOnClose);
}

SMonthPage::~SMonthPage()
{
	delete m_ptr;
}

QString SMonthPage::title() const
{
	return QLocale().monthName(m_ptr->month).toUpper() + ", "
			+ QString::number(m_ptr->year);
}

QDate SMonthPage::date() const
{
	return m_ptr->date;
}

void SMonthPage::setDate(const QDate &date)
{
	if (date.isValid())
		m_ptr->date = date;
}

int SMonthPage::year() const
{
	return m_ptr->year;
}

int SMonthPage::month() const
{
	return m_ptr->month;
}

void SMonthPage::setup(int year, int month)
{
	QDate currentDate(year, month, 1);
	int weekIndex = 0;

	m_ptr->daysInMonth = currentDate.daysInMonth();
	m_ptr->offset = currentDate.dayOfWeek() - 2;
	m_ptr->year = year;
	m_ptr->month = month;

	for (int n = 1; n <= m_ptr->daysInMonth; n++) {
		int dayOfWeek = QDate(m_ptr->year, m_ptr->month, n).dayOfWeek();

		m_ptr->daysX.insert(n, 48*(dayOfWeek - 1));
		m_ptr->daysY.insert(n, 48*weekIndex);

		if (dayOfWeek == 7)
			weekIndex++;
	}
}

void SMonthPage::mousePressEvent(QMouseEvent *event)
{
	if (event->button() != Qt::LeftButton) {
		event->ignore();
		return;
	}

	const QPoint &clickPos(event->pos());

	m_ptr->day = 7*(clickPos.y()/48) + clickPos.x()/48 - m_ptr->offset;

	if ((m_ptr->day > 0) && (m_ptr->day <= m_ptr->daysInMonth)
		&& clickArea().contains(clickPos)) {
		setDown(true);
		setPressed(true);
		repaint();
		event->accept();
	} else {
		event->ignore();
	}
}

QRect SMonthPage::clickArea() const
{
	return QRect(m_ptr->daysX.value(m_ptr->day),
				 m_ptr->daysY.value(m_ptr->day), 48, 48);
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

void SMonthPage::paintEvent(QPaintEvent *event)
{
	const QRect rectDay(0, 0, 48, 48);
	QPainter painter(this);

	painter.setClipping(true);
	painter.setClipRect(event->rect());
	painter.setRenderHint(QPainter::SmoothPixmapTransform);

	painter.fillRect(0, 0, 336, 288, Qt::white);

	painter.setPen(palette().color(QPalette::Light));

	for (int n = 0; n < 5; n++)
		painter.drawLine(9, m_ptr->baseLines.value(n),
						 327, m_ptr->baseLines.value(n));

	for (int n = 1; n <= m_ptr->daysInMonth; n++) {
		const QPoint topLeft(m_ptr->daysX.value(n), m_ptr->daysY.value(n));
		bool selected = QDate(m_ptr->year, m_ptr->month, n) == m_ptr->date;

		QPixmap canvas(48, 48);
		QPainter canvasPainter;

		canvas.fill(Qt::transparent);

		canvasPainter.begin(&canvas);
		canvasPainter.setPen(palette().color(selected
											 ? QPalette::HighlightedText
											 : (n + m_ptr->offset) % 7 + 1 > 5
											   ? QPalette::Mid
											   : QPalette::ButtonText));
		canvasPainter.drawText(rectDay, Qt::AlignCenter, QString::number(n));

		painter.translate(topLeft);

		if (selected)
			painter.fillRect(rectDay, palette().color(QPalette::Highlight));

		if (isDown() && (rectDay.translated(topLeft) == clickArea())) {
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

void SMonthPage::doClick()
{
	auto *timer = new QTimer(this);

	m_ptr->date = QDate(m_ptr->year, m_ptr->month, m_ptr->day);
	update();

	timer->setSingleShot(true);
	timer->start(150);

	connect(timer, &QTimer::timeout, this, &SMonthPage::onTimeout);
}

void SMonthPage::onTimeout()
{
	sender()->deleteLater();

	emit dateChanged(m_ptr->date);
}

SMonthPagePrivate::SMonthPagePrivate() :
	date(QDate::currentDate()),
	daysInMonth(0),
	offset(0),
	year(0),
	month(0),
	day(0)
{

}
