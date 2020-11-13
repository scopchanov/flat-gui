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

SplitView::SplitView(QWidget *parent) :
	QWidget(parent),
	m_ptr(new SplitViewPrivate(this))
{

}

SplitView::~SplitView()
{
	delete m_ptr;
}

void SplitView::setBaseWidget(QWidget *widget)
{
	if (!widget)
		return;

	widget->setParent(this);
	m_ptr->baseWidget = widget;
}

void SplitView::setSideWidget(QWidget *widget, bool hidden)
{
	if (!widget)
		return;

	widget->setParent(this);
	m_ptr->sideWidget = widget;
	m_ptr->slideIn = hidden;

	m_ptr->doLayout(m_ptr->splitSide == ST_Left
					? (hidden ? -m_ptr->sideWidget->width() : 0)
					: (hidden ? width() : width() - m_ptr->sideWidget->width()));
}

SplitView::SideType SplitView::splitSide() const
{
	return static_cast<SideType>(m_ptr->splitSide);
}

void SplitView::setSplitSide(SplitView::SideType sd)
{
	m_ptr->splitSide = sd;
}

void SplitView::toggleSideWidget()
{
	if (m_ptr->busy || !m_ptr->sideWidget)
		return;

	auto *animation = new QVariantAnimation(this);

	m_ptr->busy = true;

	animation->setStartValue(m_ptr->splitSide == ST_Left
							 ? (m_ptr->slideIn ? -m_ptr->sideWidget->width() : 0)
							 : (m_ptr->slideIn ? 0 : m_ptr->sideWidget->width()));
	animation->setEndValue(m_ptr->splitSide == ST_Left
						   ? (m_ptr->slideIn ? 0 : -m_ptr->sideWidget->width())
						   : (m_ptr->slideIn ? m_ptr->sideWidget->width() : 0));
	animation->setDuration(150);

	connect(animation, &QVariantAnimation::valueChanged,
			this, &SplitView::onValueChanged);
	connect(animation, &QVariantAnimation::finished,
			this, &SplitView::onAnimationFinished);

	animation->start(QVariantAnimation::DeleteWhenStopped);
}

void SplitView::resizeEvent(QResizeEvent *)
{
	if (!m_ptr->sideWidget)
		return;

	m_ptr->doLayout(m_ptr->splitSide == ST_Left
					? (m_ptr->slideIn ? -m_ptr->sideWidget->width() : 0)
					: (m_ptr->slideIn ? 0: m_ptr->sideWidget->width()));
}

void SplitView::onValueChanged(const QVariant &value)
{
	m_ptr->doLayout(value.toInt());
}

void SplitView::onAnimationFinished()
{
	m_ptr->slideIn ^= true;
	m_ptr->busy = false;

	toggled(!m_ptr->slideIn);
}

SplitViewPrivate::SplitViewPrivate(SplitView *parent) :
	p_ptr(parent),
	baseWidget(nullptr),
	sideWidget(nullptr),
	splitSide(SplitView::ST_Left),
	busy(false),
	slideIn(false)
{

}

void SplitViewPrivate::doLayout(int x)
{
	if (!baseWidget || !sideWidget)
		return;

	int h = p_ptr->height();
	int w = p_ptr->width() - x;
	bool leftSide = splitSide == SplitView::ST_Left;

	x = leftSide ? x : w;

	baseWidget->setGeometry(leftSide ? x + sideWidget->width() : 0, 0,
							leftSide ? w - sideWidget->width() : w, h);
	sideWidget->setGeometry(x, 0, sideWidget->width(), h);
}
