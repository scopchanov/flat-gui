#include "TransitionManager.h"
#include "TransitionManager_p.h"
#include "DurationScheme.h"
#include "PageCapture.h"
#include "PageTransition.h"
#include "composers/AbstractEffectsComposer.h"
#include <QVariantAnimation>

namespace FlatGui::Cdk::Transitions {
TransitionManager::TransitionManager(QObject *parent) :
	QObject{parent},
	_d{new TransitionManagerPrivate(this)}
{

}

TransitionManager::~TransitionManager()
{
	delete _d;
}

Qt::Orientation TransitionManager::orientation() const
{
	return _d->orientation;
}

void TransitionManager::setOrientation(Qt::Orientation orientation)
{
	if (_d->busy)
		return;

	_d->orientation = orientation;
}

AbstractEffectsComposer *TransitionManager::effectsComposer() const
{
	return _d->effectsComposer;
}

void TransitionManager::setEffectsComposer(AbstractEffectsComposer *composer)
{
	if (_d->busy || _d->effectsComposer == composer)
		return;

	_d->removeExistingComposer();

	if (composer)
		composer->setParent(this);

	_d->effectsComposer = composer;
}

QWidget *TransitionManager::pageA() const
{
	return _d->pageA;
}

void TransitionManager::setPageA(QWidget *page)
{
	if (_d->busy)
		return;

	_d->pageA = page;
}

QWidget *TransitionManager::pageB() const
{
	return _d->pageB;
}

void TransitionManager::setPageB(QWidget *page)
{
	if (_d->busy)
		return;

	_d->pageB = page;
}

bool TransitionManager::isForward() const
{
	return _d->forward;
}

void TransitionManager::setForward(bool forward)
{
	if (_d->busy)
		return;

	_d->forward = forward;
}

DurationType TransitionManager::durationType() const
{
	return _d->durationType;
}

void TransitionManager::setDurationType(DurationType durationType)
{
	if (_d->busy)
		return;

	_d->durationType = durationType;
}

DurationScheme *TransitionManager::durationScheme() const
{
	return _d->durationScheme;
}

bool TransitionManager::isBusy() const
{
	return _d->busy;
}

void TransitionManager::start()
{
	if (!_d->canStart())
		return;

	_d->busy = true;
	_d->setupPages();

	// Ensures pageB has done resizing
	QMetaObject::invokeMethod(this, [this](){
		_d->beginTransition();
	}, Qt::QueuedConnection);
}

TransitionManagerPrivate::TransitionManagerPrivate(TransitionManager *parent) :
	p{parent},
	effectsComposer{nullptr},
	pageA{nullptr},
	pageB{nullptr},
	forward{true},
	orientation{Qt::Horizontal},
	durationType{DT_Normal},
	durationScheme{new DurationScheme(parent)},
	busy{false}
{

}

void TransitionManagerPrivate::removeExistingComposer()
{
	if (!effectsComposer)
		return;

	effectsComposer->deleteLater();
	effectsComposer = nullptr;
}

void TransitionManagerPrivate::setupPages()
{
	pageA->setAttribute(Qt::WA_TransparentForMouseEvents);
	pageB->setAttribute(Qt::WA_TransparentForMouseEvents);

	pageB->lower();
	pageB->show();
	pageB->resize(pageB->parentWidget()->size());
}

void TransitionManagerPrivate::beginTransition()
{
	hidePages();
	animate();
}

void TransitionManagerPrivate::hidePages()
{
	pageA->hide();
	pageB->hide();
}

void TransitionManagerPrivate::animate()
{
	auto *transition{new PageTransition(parentWidget())};

	transition->setForward(forward);
	transition->setDuration(durationScheme->duration(durationType));
	transition->resize(parentWidget()->size());
	transition->setSnapshotA(PageCapture::createSnapshot(pageA));
	transition->setSnapshotB(PageCapture::createSnapshot(pageB));
	transition->setOrientation(orientation);

	effectsComposer->compose(transition);

	transition->show();
	transition->start();

	QObject::connect(transition, &PageTransition::destroyed, p, [this](){
		endTransition();
	});
}

void TransitionManagerPrivate::endTransition()
{
	busy = false;

	pageB->show();
	pageB->raise();

	pageA->setAttribute(Qt::WA_TransparentForMouseEvents, false);
	pageB->setAttribute(Qt::WA_TransparentForMouseEvents, false);

	emit p->finished();
}

bool TransitionManagerPrivate::canStart() const
{
	return parentWidget() && effectsComposer && pageA && pageB && !busy;
}

QWidget *TransitionManagerPrivate::parentWidget() const
{
	return qobject_cast<QWidget *>(p->parent());
}
}
