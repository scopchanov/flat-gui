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

#include "MonthView.h"
#include "cdk/HorizontalSlide.h"

MonthView::MonthView(QWidget *parent) :
	QWidget(parent),
	m_page(new MonthPage(this)),
	m_transitionInProgress(false)
{
	connect(m_page, &MonthPage::dateChanged, this, &MonthView::dateChanged);
}

QString MonthView::title() const
{
	return m_page->title();
}

QDate MonthView::date() const
{
	return m_page->date();
}

void MonthView::setDate(const QDate &date)
{
	m_page->setup(date.year(), date.month());
	m_page->setDate(date);
}

void MonthView::resizeEvent(QResizeEvent *)
{
	m_page->resize(size());
}

void MonthView::onDecClicked()
{
	slide(false);
}

void MonthView::onIncClicked()
{
	slide(true);
}

void MonthView::slide(bool left)
{
	if (!m_transitionInProgress) {
		const auto &datePage(QDate(m_page->year(),
								   m_page->month(), 1).addMonths(left
																 ? 1 : -1));
		auto *transition = new HorizontalSlide(this);
		auto *page = new MonthPage(this);

		page->setup(datePage.year(), datePage.month());
		page->setDate(m_page->date());

		m_transitionInProgress = true;

		transition->setCurrentPage(m_page);
		transition->setNextPage(page);
		transition->setDirection(left ? HorizontalSlide::SD_SlideLeft
									  : HorizontalSlide::SD_SlideRight);
		transition->setDuration(300);
		transition->start();

//		connect(transition, &HorizontalSlide::finished,
//				this, &MonthView::onSlideFinished);
//		connect(page, &MonthPage::dateChanged,
//				this, &MonthView::dateChanged);
	}
}

void MonthView::onSlideFinished()
{
	m_transitionInProgress = false;
	m_page->close();
	m_page = static_cast<MonthPage *>(
				 static_cast<HorizontalSlide *>(sender())->nextPage());

	monthChanged(m_page->title());
}
