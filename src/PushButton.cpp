#include "PushButton.h"
#include "PushButton_p.h"
#include <QVariantAnimation>
#include <QPainter>
#include <QPaintEvent>

/*!
 * \class PushButton
 * \inmodule FlatGui
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

void PushButton::setDefault(bool b)
{
	if (b)
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

		connect(animation, &QVariantAnimation::valueChanged, this, &PushButton::onHighlightChanged);
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
	canvasPainter.setOpacity(m_down ? 0.8 : 1);
	canvasPainter.drawText(rect(), Qt::AlignCenter, m_ptr->text);

	if (m_ptr->highlight) {
		painter.setOpacity(m_ptr->highlight);
		painter.fillRect(rect(), palette().color(QPalette::Highlight));
		painter.setOpacity(1);
	}

	if (m_down) {
		painter.translate(rect().center());
		painter.scale(0.96, 0.96);
		painter.translate(-rect().center());
	}

	painter.drawPixmap(rect(), canvas);
}

void PushButton::setSize()
{
	int w = fontMetrics().width(m_ptr->text) + 18;

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
