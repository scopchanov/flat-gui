#include "PageTransition.h"
#include "PageTransition_p.h"
#include "TransitionOptions.h"
#include "effects/AbstractTransitionEffect.h"
#include <QVariantAnimation>
#include <QPaintEvent>
#include <QPainter>

namespace FlatGui::Cdk::Transitions {
PageTransition::PageTransition(QWidget *parent) :
	QWidget{parent},
	_d{new PageTransitionPrivate(this)}

{
	setAutoFillBackground(true);

	_d->animation->setStartValue(0.0);
	_d->animation->setEndValue(1.0);

#ifdef QT_NO_DEBUG
	connect(_d->animation, &QVariantAnimation::valueChanged,
			this, qOverload<>(&PageTransition::update));
#else
	connect(_d->animation, &QVariantAnimation::valueChanged,
			this, qOverload<>(&PageTransition::repaint));
#endif

	connect(_d->animation, &QVariantAnimation::finished,
			this, &PageTransition::deleteLater);
}

PageTransition::~PageTransition()
{
	delete _d;
}

QPixmap PageTransition::snapshotA() const
{
	return _d->snapshotA;
}

void PageTransition::setSnapshotA(const QPixmap &snapshot)
{
	if (_d->isRunning() || snapshot.isNull())
		return;

	_d->snapshotA = snapshot;
}

QPixmap PageTransition::snapshotB() const
{
	return _d->snapshotB;
}

void PageTransition::setSnapshotB(const QPixmap &snapshot)
{
	if (_d->isRunning() || snapshot.isNull())
		return;

	_d->snapshotB = snapshot;
}

Qt::Orientation PageTransition::orientation() const
{
	return _d->orientation;
}

void PageTransition::setOrientation(Qt::Orientation orientation)
{
	if (_d->isRunning())
		return;

	_d->orientation = orientation;
}

bool PageTransition::isForward() const
{
	return _d->animation->direction() == QVariantAnimation::Forward;
}

void PageTransition::setForward(bool forward)
{
	if (_d->isRunning())
		return;

	_d->animation->setDirection(forward ? QVariantAnimation::Forward
										: QVariantAnimation::Backward);
}

int PageTransition::duration() const
{
	return _d->animation->duration();
}

void PageTransition::setDuration(int duration)
{
	if (duration <= 0 || _d->isRunning())
		return;

	_d->animation->setDuration(duration);
}

QEasingCurve PageTransition::easingCurve() const
{
	return _d->animation->easingCurve();
}

void PageTransition::setEasingCurve(const QEasingCurve &easing)
{
	if (_d->isRunning())
		return;

	_d->animation->setEasingCurve(easing);
}

void PageTransition::addEffect(AbstractTransitionEffect *effect)
{
	if (_d->isRunning() || !effect || _d->effects.contains(effect))
		return;

	effect->setParent(this);

	_d->effects.append(effect);
}

AbstractTransitionEffect *PageTransition::effect(qsizetype index) const
{
	bool isValidIndex{index >= 0 && index < _d->effects.count()};

	return isValidIndex ? _d->effects.at(index) : nullptr;
}

void PageTransition::start()
{
	if (_d->isRunning())
		return;

	_d->effects.isEmpty() ? deleteLater() : _d->animation->start();
}

void PageTransition::paintEvent(QPaintEvent *event)
{
	QPainter painter(this);
	qreal value{_d->animation->currentValue().toReal()};
	qreal invertedValue{1.0 - value};
	bool isForward{_d->animation->direction() == QVariantAnimation::Forward};

	painter.setClipping(true);
	painter.setClipRect(event->rect());
	painter.setRenderHint(QPainter::SmoothPixmapTransform);

	_d->applyEffects(&painter, {value, invertedValue, isForward, rect()});
}

PageTransitionPrivate::PageTransitionPrivate(PageTransition *parent) :
	p{parent},
	orientation{Qt::Horizontal},
	animation{new QVariantAnimation(parent)}
{

}

void PageTransitionPrivate::applyEffects(QPainter *painter, const TransitionOptions &options)
{
	for (auto *effect : std::as_const(effects))
		effect->apply(painter, options);
}

bool PageTransitionPrivate::isRunning() const
{
	return animation->state() != QVariantAnimation::Stopped;
}
}
