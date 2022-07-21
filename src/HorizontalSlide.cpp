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

#include "HorizontalSlide.h"
#include "HorizontalSlide_p.h"
#include <QVariantAnimation>
#include <QLabel>

/*!
	\class HorizontalSlide
	\inmodule CDK
	\ingroup libraries
	\brief Provides a horizontal sliding transition between two pages.

	The class provides an interface for managing a horizontal sliding
	transition between two pages. The currentPage property holds the page from
	which the transition should start. The nextPage property holds the page to
	which should be trainsitioned. Each QWidget subclass can be used as a page.
	The direction of the transition is held by the direction property and the
	duration - by the duration property.

	The trasnition is started by calling start slot. The inProgress property
	shows wether the transition is currently in progress.

	This class is a part of the CDK and can be used for the development of
	custom GUI components.
 */

/*!
	\enum HorizontalSlide::SlideDirection

	SlideDirection is used to specify in which direction the transition between
	the two pages should take place.

	\value SD_SlideLeft Indicates a sliding transition from right to left.
	\value SD_SlideRight Indicates a sliding transition from left to right.

	\sa direction(), setDirection(), {SlideView}
 */

/*!
	Constructs a HorizontalSlide instance with a given \a parent.
 */

HorizontalSlide::HorizontalSlide(QWidget *parent) :
	QWidget(parent),
	m_ptr(new HorizontalSlidePrivate(this))
{

}

HorizontalSlide::~HorizontalSlide()
{
	delete m_ptr;
}

/*!
	\property HorizontalSlide::currentPage
	\brief The page from which the transition should start.

	This property's default is \c nullptr.
 */

QWidget *HorizontalSlide::currentPage() const
{
	return m_ptr->currentPage;
}

void HorizontalSlide::setCurrentPage(QWidget *page)
{
	if (m_ptr->inProgress || m_ptr->currentPage == page)
		return;

	m_ptr->currentPage = page;

	emit currentPageChanged();
}

/*!
	\property HorizontalSlide::nextPage
	\brief The page to which should be trainsitioned.

	This property's default is \c nullptr.
 */

QWidget *HorizontalSlide::nextPage() const
{
	return m_ptr->nextPage;
}

void HorizontalSlide::setNextPage(QWidget *page)
{
	if (m_ptr->inProgress || m_ptr->nextPage == page)
		return;

	m_ptr->nextPage = page;

	emit nextPageChanged();
}

/*!
	\property HorizontalSlide::direction
	\brief The direction of the transition.

	This property's default is \c SD_SlideLeft.
 */

HorizontalSlide::SlideDirection HorizontalSlide::direction() const
{
	return static_cast<SlideDirection>(m_ptr->direction);
}

void HorizontalSlide::setDirection(SlideDirection direction)
{
	if (m_ptr->inProgress || m_ptr->direction == direction)
		return;

	m_ptr->direction = direction;

	emit directionChanged();
}

/*!
	\property HorizontalSlide::duration
	\brief The duration of the transition.

	This property's default is \c 250.
 */

int HorizontalSlide::duration() const
{
	return m_ptr->duration;
}

void HorizontalSlide::setDuration(int duration)
{
	if (m_ptr->inProgress || m_ptr->duration == duration)
		return;

	m_ptr->duration = duration;

	emit durationChanged();
}

/*!
	\property HorizontalSlide::inProgress
	\brief Wether the transition is currently in progress.

	This property's default is \c false.
 */

bool HorizontalSlide::inProgress() const
{
	return m_ptr->inProgress;
}

/*!
	Starts the transition.
 */

void HorizontalSlide::start()
{
	if (m_ptr->inProgress)
		return;

	show();
	m_ptr->startSlide();
}

HorizontalSlidePrivate::HorizontalSlidePrivate(HorizontalSlide *parent) :
	p_ptr(parent),
	currentPage(nullptr),
	nextPage(nullptr),
	labCurrent(new QLabel(p_ptr)),
	labNext(new QLabel(p_ptr)),
	direction(HorizontalSlide::SD_SlideLeft),
	duration(250),
	inProgress(false)
{
	labCurrent->hide();
	labNext->hide();
}

HorizontalSlidePrivate::~HorizontalSlidePrivate()
{
	delete labCurrent;
	delete labNext;
}

void HorizontalSlidePrivate::startSlide()
{
	if (!currentPage || !nextPage)
		return;

	setInProgress(true);

	auto *animation = new QVariantAnimation(p_ptr);
	bool slideLeft = direction == HorizontalSlide::SD_SlideLeft;

	currentPage->hide();
	nextPage->hide();

	labCurrent->setPixmap(makeSnapshot(currentPage));
	labCurrent->show();

	labNext->setPixmap(makeSnapshot(nextPage));
	labNext->show();
	labNext->move(p_ptr->width(), 0);

	animation->setStartValue(slideLeft ? 0 : currentPage->width());
	animation->setEndValue(slideLeft ? currentPage->width() : 0);
	animation->setDuration(duration);
	animation->setEasingCurve(QEasingCurve::InOutQuad);

	QObject::connect(animation, &QVariantAnimation::valueChanged,
					 [this](const QVariant &value){
		int n = -value.toInt();
		int m = currentPage->width() + n;
		bool slideLeft = direction == HorizontalSlide::SD_SlideLeft;

		labCurrent->move(slideLeft ? n : m, 0);
		labNext->move(slideLeft ? m : n, 0);
	});

	QObject::connect(animation, &QVariantAnimation::finished,
					 [this](){
		labCurrent->hide();
		labNext->hide();
		nextPage->show();

		setInProgress(false);
	});

	animation->start(QVariantAnimation::DeleteWhenStopped);
}

QPixmap HorizontalSlidePrivate::makeSnapshot(QWidget *page)
{
	QPixmap pixmap(page->size());

	page->render(&pixmap);

	return pixmap;
}

void HorizontalSlidePrivate::setInProgress(bool value)
{
	if (inProgress == value)
		return;

	inProgress = value;

	emit p_ptr->inProgressChanged();
}
