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
	\inmodule Components
	\ingroup Layouts
	\brief Provides a container for stacked widgets.

	The pages are shown one at a time. SlideView switches from one page
	to another using a horizontal sliding transition. Pages are added to
	the view using addPage or addPageStacked. Any class inheriting from QWidget
	could be used as a page.
 */

/*!
	Constructs a SlideView instance with a given \a parent.
 */

SlideView::SlideView(QWidget *parent) :
	QWidget(parent),
	m_ptr(new SlideViewPrivate(this))
{
	setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
}

SlideView::~SlideView()
{
	delete m_ptr;
}

/*!
	Appends the page \a page to the children of this class. This function emits
	the pageCountChanged signal.

	\sa pageCount(), currentPage()
*/

void SlideView::appendPage(QWidget *page)
{
	if (!page || m_ptr->pages.contains(page))
		return;

	bool isFirstPage{m_ptr->pages.isEmpty()};

	page->setParent(this);
	page->setVisible(isFirstPage);

	m_ptr->pages.append(page);

	emit pageCountChanged();

	if (!isFirstPage)
		return;

	m_ptr->currentIndex = 0;

	emit currentIndexChanged();
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

QWidget *SlideView::currentPage() const
{
	return m_ptr->pages.at(m_ptr->currentIndex);
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

void SlideView::removeRemainingPages()
{
	while (m_ptr->currentIndex < m_ptr->pages.count() - 1)
		m_ptr->pages.removeLast();
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
	the index is out of bounds or this were the current page, this function does
	nothing.
 */

void SlideView::gotoPage(int index, int duration)
{
	if (m_ptr->currentIndex == index
		|| index < 0
		|| index >= m_ptr->pages.count())
		return;

	m_ptr->slideToPage(index, duration);
}

/*!
	\reimp
 */

void SlideView::resizeEvent(QResizeEvent *)
{
	if (!m_ptr->pages.isEmpty())
		m_ptr->pages.at(m_ptr->currentIndex)->resize(size());
}

SlideViewPrivate::SlideViewPrivate(SlideView *parent) :
	p_ptr(parent),
	currentIndex(-1),
	nextIndex(-1),
	busy(false)
{

}

void SlideViewPrivate::slideToPage(int index, int duration)
{
	if (busy
		|| pages.isEmpty()
		|| (currentIndex < 0)
		|| (index == currentIndex)
		|| (duration < 0))
		return;

	auto *transition = new HorizontalSlide(p_ptr);

	busy = true;
	pages.at(index)->resize(p_ptr->size());

	transition->resize(p_ptr->size());
	transition->setCurrentPage(pages.at(currentIndex));
	transition->setNextPage(pages.at(index));
	transition->setDirection(index > currentIndex
							 ? HorizontalSlide::SD_SlideLeft
							 : HorizontalSlide::SD_SlideRight);
	transition->setDuration(duration);

	QObject::connect(transition, &HorizontalSlide::inProgressChanged,
					 [this, transition](){
		if (transition->inProgress())
			return;

		currentIndex = pages.indexOf(transition->nextPage());
		busy = false;

		emit p_ptr->currentIndexChanged();
		transition->deleteLater();
	});

	transition->start();
}
