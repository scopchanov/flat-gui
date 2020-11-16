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

#include "SlideView.h"
#include "SlideView_p.h"
#include "HorizontalSlide.h"

/*!
	\class SlideView
	\inmodule FlatGui
	\brief Provides a container for stacked widgets.

	The pages are shown one at a time. SlideView switches from one page
	to another using a horizontal sliding animation. Pages are added to
	the view using addPage or addPageStacked. Any class inheriting from QWidget
	could be used as a page.
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
	\property SlideView::pageCount
	\brief The count of the pages, which has been added to the view.

	This property's default is \c 0.
 */

int SlideView::pageCount() const
{
	return m_ptr->pages.count();
}

/*!
	\property SlideView::currentIndex
	\brief The index of the currently displayed page, or \c -1 if no pages has
	been added to the view.

	This property's default is \c -1.
 */

int SlideView::currentIndex() const
{
	return m_ptr->currentIndex;
}

void SlideView::setCurrentIndex(int index)
{
	if (m_ptr->currentIndex == index)
		return;

	m_ptr->currentIndex = index;

	emit currentIndexChanged();
}

/*!
	Sets the \a page as the first page displayed by the view.
	The page is added to the list of the pages and shown.
	The pageCountChanged, currentIndexChanged and currentPageChanged signals
	are emitted. If a \c nullptr is passed as an argument, this function does
	nothing.
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

	emit pageCountChanged();
	emit currentIndexChanged();
	emit currentPageChanged(page->windowTitle());
}

/*!
	Adds the page \a page to the children of this class and to the stack of
	pages. This function emits the pageCountChanged signal.

	\sa addHomePage(), addPageStacked()
*/

void SlideView::addPage(QWidget *page)
{
	if (!page || m_ptr->pages.isEmpty())
		return;

	page->setParent(this);

	while (m_ptr->currentIndex < m_ptr->pages.count() - 1)
		m_ptr->pages.takeLast();

	m_ptr->pages.append(page);

	emit pageCountChanged();

	page->resize(size());
	gotoNextPage();
}

/*!
	Adds the page \a page to the children of this class. This function emits
	the pageCountChanged signal.

	\sa addHomePage(), addPage()
*/

void SlideView::addPageStacked(QWidget *page)
{
	if (!page || m_ptr->pages.isEmpty())
		return;

	page->setParent(this);

	m_ptr->pages.append(page);

	emit pageCountChanged();
}

/*!
	Slides the previous page into the view, i.e. the page with index smaller by
	one than the index of the current page.

	This is a convenience function. It is equivalent to calling gotoPage(
	currentIndex() - 1, 300).

	\sa gotoPage()
 */

void SlideView::gotoPreviousPage()
{
	gotoPage(m_ptr->currentIndex - 1, 300);
}

/*!
	Slides the first page into the view, i.e. the page with the index 0.

	This is a convenience function. It is equivalent to calling gotoPage(0,
	100).

	\sa gotoPage()
 */

void SlideView::gotoFirstPage()
{
	gotoPage(0, 100);
}

/*!
	Slides the next page into the view, i.e. the page with index larger by one
	than the index of the current page.

	This is a convenience function. It is equivalent to calling gotoPage(
	currentIndex() + 1, 300).

	\sa gotoPage()
 */

void SlideView::gotoNextPage()
{
	gotoPage(m_ptr->currentIndex + 1, 300);
}

/*!
	Slides the page with index \a index into the view for \a duration ms. If
	this were the current page, this function does nothing.
 */

void SlideView::gotoPage(int index, int duration)
{
	if ((index < 0) || (m_ptr->currentIndex == index))
		return;

	m_ptr->slideToPage(index, duration);
}

/*!
	\reimp
 */

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

void SlideViewPrivate::slideToPage(int n, int duration)
{
	if (busy
		|| pages.isEmpty()
		|| (currentIndex < 0)
		|| (n == currentIndex)
		|| (duration < 0))
		return;

	auto *transition = new HorizontalSlide(p_ptr);

	busy = true;

	transition->setCurrentPage(pages.at(currentIndex));
	transition->setNextPage(pages.at(n));
	transition->start(n > currentIndex, duration);

	QObject::connect(transition, &HorizontalSlide::finished,
					 [this, transition](){
		currentIndex = pages.indexOf(transition->nextPage());
		busy = false;

		p_ptr->currentIndexChanged();
		p_ptr->currentPageChanged(pages.at(currentIndex)->windowTitle());
	});
}
