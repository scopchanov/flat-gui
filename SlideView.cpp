#include "SlideView.h"
#include "SlideView_p.h"
#include "HorizontalSlide.h"

/*!
 * \class SlideView
 * \inmodule FlatGui
 * \brief Provides a container of stacked widgets
 *
 * The pages are shown one at a time. SlideView switches from one page
 * to another using a horizontal sliding animation. Pages are added to
 * the view using addPage. Any class inheriting from QWidget could be
 * used as a page.
 */

SlideView::SlideView(QWidget *parent) :
	QWidget(parent),
	m_ptr(new SlideViewPrivate(this))
{
	setAttribute(Qt::WA_OpaquePaintEvent);
}

SlideView::~SlideView()
{
	delete m_ptr;
}

/*!
 * \brief Sets the \a page as the first page displayed by the view.
 * The page is added to the list of the pages and shown.
 * The countChanged, currentIndexChanged and currentPageChanged signals
 * are emitted. If a nullptr is passed as an argument this function does
 * nothing.
 */

void SlideView::addHomePage(QWidget *page)
{
	if (!page)
		return;

	m_ptr->pages.clear();
	m_ptr->pages.append(page);
	m_ptr->currentIndex = 0;

	page->setParent(this);
	page->show();

	countChanged(1);
	currentIndexChanged(0, 1);
	currentPageChanged(page->windowTitle());
}

/*!
 * \brief SlideView::addPage
 */

void SlideView::addPage(QWidget *page, bool dontStack)
{
	if (!page || m_ptr->pages.isEmpty())
		return;

	page->setParent(this);

	if (dontStack)
		while (m_ptr->currentIndex < m_ptr->pages.count() - 1)
			m_ptr->pages.takeLast();

	m_ptr->pages.append(page);

	countChanged(m_ptr->pages.count());

	if (dontStack) {
		page->resize(size());
		gotoNextPage();
	}
}

/*!
 * \brief SlideView::gotoPreviousPage
 */

void SlideView::gotoPreviousPage()
{
	if (m_ptr->currentIndex < 1)
		return;

	m_ptr->slideToPage(m_ptr->currentIndex - 1, 300);
}

/*!
 * \brief SlideView::gotoFirstPage
 */

void SlideView::gotoFirstPage()
{
	if (m_ptr->currentIndex < 1)
		return;

	m_ptr->slideToPage(0, 100);
}

/*!
 * \brief SlideView::gotoNextPage
 */

void SlideView::gotoNextPage()
{
	if (m_ptr->currentIndex > m_ptr->pages.count() - 2)
		return;

	m_ptr->slideToPage(m_ptr->currentIndex + 1, 300);
}

/*!
 * \brief SlideView::gotoPage
 */

void SlideView::gotoPage(int n)
{
	if ((n < 0) || (m_ptr->currentIndex == n))
		return;

	m_ptr->slideToPage(n, 300);
}

void SlideView::resizeEvent(QResizeEvent *)
{
	if (m_ptr->currentIndex >= 0)
		m_ptr->pages.at(m_ptr->currentIndex)->resize(size());
}

SlideViewPrivate::SlideViewPrivate(SlideView *parent) :
	p_ptr(parent),
	currentIndex(-1),
	nextIndex(-1),
	busy(false)
{

}

void SlideViewPrivate::slideToPage(int n, int speed)
{
	if (busy
		|| pages.isEmpty()
		|| (currentIndex < 0)
		|| (n == currentIndex)
		|| (speed < 0))
		return;

	auto *transition = new HorizontalSlide(p_ptr);

	busy = true;

	transition->setCurrentPage(pages.at(currentIndex));
	transition->setNextPage(pages.at(n));
	transition->start(n > currentIndex, speed);

	QObject::connect(transition, &HorizontalSlide::finished, [this, transition](){
		currentIndex = pages.indexOf(transition->nextPage());
		busy = false;

		p_ptr->currentIndexChanged(currentIndex, pages.count());
		p_ptr->currentPageChanged(pages.at(currentIndex)->windowTitle());
	});
}
