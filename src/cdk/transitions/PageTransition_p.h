#ifndef PAGETRANSITION_P_H
#define PAGETRANSITION_P_H

#include <QtCore/qglobal.h>
#include <QPixmap>
#include <QList>

class QVariantAnimation;
class QPainter;

namespace FlatGui::Cdk::Transitions {
class AbstractTransitionEffect;
class PageTransition;
class TransitionOptions;

class PageTransitionPrivate
{
	Q_DISABLE_COPY(PageTransitionPrivate)

	explicit PageTransitionPrivate(PageTransition *parent);

	void applyEffects(QPainter *painter, const TransitionOptions &options);
	bool isRunning() const;

	PageTransition *p;
	QPixmap snapshotA;
	QPixmap snapshotB;
	Qt::Orientation orientation;
	QVariantAnimation *animation;
	QList<AbstractTransitionEffect *> effects;

	friend class PageTransition;
};
}

#endif // PAGETRANSITION_P_H
