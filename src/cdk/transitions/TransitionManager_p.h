#ifndef TRANSITIONMANAGER_P_H
#define TRANSITIONMANAGER_P_H

#include <QPointer>
#include "global/FlatGuiEnums.h"

class QWidget;

namespace FlatGui::Cdk::Transitions {
class TransitionManager;
class AbstractEffectsComposer;
class DurationScheme;
class PageTransition;

class TransitionManagerPrivate
{
	Q_DISABLE_COPY(TransitionManagerPrivate)

	explicit TransitionManagerPrivate(TransitionManager *parent);

	void removeExistingComposer();
	void setupPages();
	void beginTransition();
	void hidePages();
	void animate();
	void endTransition();
	bool canStart() const;
	QWidget *parentWidget() const;

	TransitionManager *p;
	AbstractEffectsComposer *effectsComposer;
	QPointer<QWidget> pageA;
	QPointer<QWidget> pageB;
	bool forward;
	Qt::Orientation orientation;
	DurationType durationType;
	DurationScheme *durationScheme;
	bool busy;

	friend class TransitionManager;
};
}

#endif // TRANSITIONMANAGER_P_H
