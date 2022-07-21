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

#include "PushButton.h"
#include "PushButton_p.h"
#include <QVariantAnimation>
#include <QPainter>
#include <QPaintEvent>

/*!
	\class PushButton
	\inmodule Components
	\ingroup Layouts
	\brief
 */

PushButton::PushButton(QWidget *parent) :
	AbstractButton(parent),
	m_ptr(new PushButtonPrivate)
{
	setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Fixed);
	setForegroundRole(QPalette::ButtonText);
	setFocusPolicy(Qt::StrongFocus);
	setFixedHeight(48);
}

PushButton::~PushButton()
{
	delete m_ptr;
}

void PushButton::setText(const QString &text)
{
	m_ptr->text = text;

	setSize();
}

void PushButton::setDefault(bool value)
{
	if (value)
		setForegroundRole(QPalette::Highlight);
}

bool PushButton::event(QEvent *event)
{
	if (event->type() != QEvent::EnabledChange)
		return AbstractButton::event(event);

	if (isEnabled()) {
		auto *animation = new QVariantAnimation(this);

		animation->setStartValue(0.0);
		animation->setKeyValueAt(0.5, 1.0);
		animation->setEndValue(0.0);
		animation->setDuration(1500);
		animation->setEasingCurve(QEasingCurve::OutBack);
		animation->start(QVariantAnimation::DeleteWhenStopped);

		connect(animation, &QVariantAnimation::valueChanged,
				this, &PushButton::onHighlightChanged);
	}

	repaint();
	event->accept();
	return true;
}

void PushButton::paintEvent(QPaintEvent *event)
{
	QPainter painter(this);

	painter.setClipping(true);
	painter.setClipRect(event->rect());
	painter.setRenderHint(QPainter::SmoothPixmapTransform);

	QPixmap canvas(size());
	QPainter canvasPainter;

	canvas.fill(Qt::transparent);

	canvasPainter.begin(&canvas);
	canvasPainter.setPen(palette().color(foregroundRole()));
	canvasPainter.setOpacity(isDown() ? 0.8 : 1);
	canvasPainter.drawText(rect(), Qt::AlignCenter, m_ptr->text);

	if (m_ptr->highlight) {
		painter.setOpacity(m_ptr->highlight);
		painter.fillRect(rect(), palette().color(QPalette::Highlight));
		painter.setOpacity(1);
	}

	if (isDown()) {
		painter.translate(rect().center());
		painter.scale(0.96, 0.96);
		painter.translate(-rect().center());
	}

	painter.drawPixmap(rect(), canvas);
}

void PushButton::setSize()
{
	int w = fontMetrics().horizontalAdvance(m_ptr->text) + 18;

	setMinimumSize(w < 100 ? 100 : w, 48);
}

void PushButton::onHighlightChanged(const QVariant &value)
{
	m_ptr->highlight = value.toDouble();
	repaint();
}

PushButtonPrivate::PushButtonPrivate() :
	highlight(0)
{

}
