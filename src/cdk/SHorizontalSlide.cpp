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

#include "SHorizontalSlide.h"
#include "SHorizontalSlide_p.h"
#include <QVariantAnimation>
#include <QLabel>

/*!
	\class SHorizontalSlide
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
	\enum SHorizontalSlide::SlideDirection

	SlideDirection is used to specify in which direction the transition between
	the two pages should take place.

	\value SD_SlideLeft Indicates a sliding transition from right to left.
	\value SD_SlideRight Indicates a sliding transition from left to right.

	\sa direction(), setDirection(), {SlideView}
 */

/*!
	Constructs a SHorizontalSlide instance with a given \a parent.
 */

SHorizontalSlide::SHorizontalSlide(QWidget *parent) :
	QWidget(parent),
	m_ptr(new SHorizontalSlidePrivate(this))
{

}

SHorizontalSlide::~SHorizontalSlide()
{
	delete m_ptr;
}

/*!
	\property SHorizontalSlide::currentPage
	\brief The page from which the transition should start.

	This property's default is \c nullptr.
 */

QWidget *SHorizontalSlide::currentPage() const
{
	return m_ptr->currentPage;
}

void SHorizontalSlide::setCurrentPage(QWidget *page)
{
	if (m_ptr->inProgress || m_ptr->currentPage == page)
		return;

	m_ptr->currentPage = page;

	emit currentPageChanged();
}

/*!
	\property SHorizontalSlide::nextPage
	\brief The page to which should be trainsitioned.

	This property's default is \c nullptr.
 */

QWidget *SHorizontalSlide::nextPage() const
{
	return m_ptr->nextPage;
}

void SHorizontalSlide::setNextPage(QWidget *page)
{
	if (m_ptr->inProgress || m_ptr->nextPage == page)
		return;

	m_ptr->nextPage = page;

	emit nextPageChanged();
}

/*!
	\property SHorizontalSlide::direction
	\brief The direction of the transition.

	This property's default is \c SD_SlideLeft.
 */

SHorizontalSlide::SlideDirection SHorizontalSlide::direction() const
{
	return static_cast<SlideDirection>(m_ptr->direction);
}

void SHorizontalSlide::setDirection(SlideDirection direction)
{
	if (m_ptr->inProgress || m_ptr->direction == direction)
		return;

	m_ptr->direction = direction;

	emit directionChanged();
}

/*!
	\property SHorizontalSlide::duration
	\brief The duration of the transition.

	This property's default is \c 250.
 */

int SHorizontalSlide::duration() const
{
	return m_ptr->duration;
}

void SHorizontalSlide::setDuration(int duration)
{
	if (m_ptr->inProgress || m_ptr->duration == duration)
		return;

	m_ptr->duration = duration;

	emit durationChanged();
}

/*!
	\property SHorizontalSlide::inProgress
	\brief Wether the transition is currently in progress.

	This property's default is \c false.
 */

bool SHorizontalSlide::inProgress() const
{
	return m_ptr->inProgress;
}

/*!
	Starts the transition.
 */

void SHorizontalSlide::start()
{
	if (m_ptr->inProgress)
		return;

	show();
	m_ptr->startSlide();
}

SHorizontalSlidePrivate::SHorizontalSlidePrivate(SHorizontalSlide *parent) :
	p_ptr(parent),
	currentPage(nullptr),
	nextPage(nullptr),
	labCurrent(new QLabel(p_ptr)),
	labNext(new QLabel(p_ptr)),
	direction(SHorizontalSlide::SD_SlideLeft),
	duration(250),
	inProgress(false)
{
	labCurrent->hide();
	labNext->hide();
}

SHorizontalSlidePrivate::~SHorizontalSlidePrivate()
{
	delete labCurrent;
	delete labNext;
}

void SHorizontalSlidePrivate::startSlide()
{
	if (!currentPage || !nextPage)
		return;

	setInProgress(true);

	auto *animation = new QVariantAnimation(p_ptr);
	bool slideLeft = direction == SHorizontalSlide::SD_SlideLeft;

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
		bool slideLeft = direction == SHorizontalSlide::SD_SlideLeft;

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

QPixmap SHorizontalSlidePrivate::makeSnapshot(QWidget *page)
{
	QPixmap pixmap(page->size());

	page->render(&pixmap);

	return pixmap;
}

void SHorizontalSlidePrivate::setInProgress(bool value)
{
	if (inProgress == value)
		return;

	inProgress = value;

	emit p_ptr->inProgressChanged();
}
