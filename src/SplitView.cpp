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

#include "SplitView.h"
#include "SplitView_p.h"
#include <QVariantAnimation>

/*!
	\class SplitView
	\inmodule Components
	\ingroup Layouts
	\brief Provides a horizontally splittable widget.
 */

/*!
	Constructs a SplitView instance with a given \a parent.
 */

SplitView::SplitView(QWidget *parent) :
	QWidget(parent),
	m_ptr(new SplitViewPrivate(this))
{

}

SplitView::~SplitView()
{
	delete m_ptr;
}

/*!
	\property SplitView::baseWidget
	\brief The widget which is constantly shown.

	This property's default is \c nullptr.
 */

QWidget *SplitView::baseWidget() const
{
	return m_ptr->baseWidget;
}

void SplitView::setBaseWidget(QWidget *widget)
{
	if (!widget || m_ptr->inProgress || m_ptr->baseWidget == widget)
		return;

	widget->setParent(this);
	m_ptr->baseWidget = widget;

	emit baseWidgetChanged();
}

/*!
	\property SplitView::sideWidget
	\brief The widget which is toggled.

	This property's default is \c nullptr.
 */

QWidget *SplitView::sideWidget() const
{
	return m_ptr->sideWidget;
}

void SplitView::setSideWidget(QWidget *widget)
{
	if (!widget || m_ptr->inProgress || m_ptr->sideWidget == widget)
		return;

	widget->setParent(this);
	m_ptr->sideWidget = widget;

	emit sideWidgetChanged();
}

/*!
	\property SplitView::splitSide
	\brief The side on which the side widget is placed.

	This property's default is SplitView::ST_Left.
 */

SplitView::SideType SplitView::splitSide() const
{
	return static_cast<SideType>(m_ptr->splitSide);
}

void SplitView::setSplitSide(SplitView::SideType side)
{
	if (m_ptr->inProgress || m_ptr->splitSide == side)
		return;

	m_ptr->splitSide = side;

	emit splitSideChanged();
}

/*!
	\property SplitView::splitDuration
	\brief The duration of the side widget's toggle transition.

	This property's default is 250.
 */

int SplitView::splitDuration() const
{
	return m_ptr->splitDuration;
}

void SplitView::setSplitDuration(int duration)
{
	if (m_ptr->inProgress || m_ptr->splitDuration == duration)
		return;

	m_ptr->splitDuration = duration;

	emit splitDurationChanged();
}

/*!
	\property SplitView::sideWidgetState
	\brief The state of the side widget.

	This property's default is SplitView::ST_Closed.
 */

SplitView::StateType SplitView::sideWidgetState() const
{
	return static_cast<StateType>(m_ptr->sideWidgetState);
}

void SplitView::openSideWidget()
{
	m_ptr->setSideWidgetState(ST_Open);

	m_ptr->layoutWidgets(m_ptr->splitSide == ST_Left
						 ? 0 : width() - m_ptr->sideWidget->width());
}

void SplitView::closeSideWidget()
{
	m_ptr->setSideWidgetState(ST_Closed);

	m_ptr->layoutWidgets(m_ptr->splitSide == ST_Left
						 ? -m_ptr->sideWidget->width() : width());
}

/*!
	Toggles the side widget with a horizontal split transition.
 */

void SplitView::toggleSideWidget()
{
	m_ptr->startTransition();
}

/*!
	\reimp
 */

void SplitView::resizeEvent(QResizeEvent *)
{
	m_ptr->resizeWidgets();
}

SplitViewPrivate::SplitViewPrivate(SplitView *parent) :
	p_ptr(parent),
	baseWidget(nullptr),
	sideWidget(nullptr),
	splitSide(SplitView::ST_Left),
	splitDuration(250),
	sideWidgetState(SplitView::ST_Closed),
	inProgress(false)
{

}

void SplitViewPrivate::startTransition()
{
	if (inProgress || !sideWidget)
		return;

	auto *animation = new QVariantAnimation(p_ptr);
	bool isLeft = splitSide == SplitView::ST_Left;
	bool isClosed = sideWidgetState == SplitView::ST_Closed;

	inProgress = true;

	animation->setStartValue(isLeft
							 ? (isClosed ? -sideWidget->width() : 0)
							 : (isClosed ? 0 : sideWidget->width()));
	animation->setEndValue(isLeft
						   ? (isClosed ? 0 : -sideWidget->width())
						   : (isClosed ? sideWidget->width() : 0));
	animation->setDuration(splitDuration);
	animation->setEasingCurve(QEasingCurve::InOutQuad);

	QObject::connect(animation, &QVariantAnimation::valueChanged,
					 [this](const QVariant &value){
		layoutWidgets(value.toInt());
	});

	QObject::connect(animation, &QVariantAnimation::finished,
					 [this](){
		setSideWidgetState(sideWidgetState == SplitView::ST_Closed
						   ? SplitView::ST_Open : SplitView::ST_Closed);

		inProgress = false;
	});

	animation->start(QVariantAnimation::DeleteWhenStopped);
}

void SplitViewPrivate::setSideWidgetState(int value)
{
	if (sideWidgetState == value)
		return;

	sideWidgetState = value;

	emit p_ptr->sideWidgetStateChanged();
}

void SplitViewPrivate::resizeWidgets()
{
	if (!sideWidget)
		return;

	bool isClosed = sideWidgetState == SplitView::ST_Closed;

	layoutWidgets(splitSide == SplitView::ST_Left
				  ? (isClosed ? -sideWidget->width() : 0)
				  : (isClosed ? 0 : sideWidget->width()));
}

void SplitViewPrivate::layoutWidgets(int x)
{
	if (!baseWidget || !sideWidget)
		return;

	bool isLeft = splitSide == SplitView::ST_Left;
	int w = p_ptr->width() - x;
	int h = p_ptr->height();

	x = isLeft ? x : w;

	baseWidget->setGeometry(isLeft ? x + sideWidget->width() : 0, 0,
							isLeft ? w - sideWidget->width() : w, h);
	sideWidget->setGeometry(x, 0, sideWidget->width(), h);
}
