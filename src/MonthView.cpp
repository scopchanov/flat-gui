#include "MonthView.h"
#include "HorizontalSlide.h"

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
		const auto &datePage(QDate(m_page->year(), m_page->month(), 1).addMonths(left ? 1 : -1));
		auto *transition = new HorizontalSlide(this);
		auto *page = new MonthPage(this);

		page->setup(datePage.year(), datePage.month());
		page->setDate(m_page->date());

		m_transitionInProgress = true;

		transition->setCurrentPage(m_page);
		transition->setNextPage(page);
		transition->start(left, 300);

		connect(transition, &HorizontalSlide::finished, this, &MonthView::onSlideFinished);
		connect(page, &MonthPage::dateChanged, this, &MonthView::dateChanged);
	}
}

void MonthView::onSlideFinished()
{
	m_transitionInProgress = false;
	m_page->close();
	m_page = static_cast<MonthPage *>(static_cast<HorizontalSlide *>(sender())->nextPage());

	monthChanged(m_page->title());
}
