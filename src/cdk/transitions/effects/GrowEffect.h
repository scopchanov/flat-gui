#ifndef GROWEFFECT_H
#define GROWEFFECT_H

#include "AbstractTransitionEffect.h"
#include "global/FlatGuiEnums.h"

namespace FlatGui::Cdk::Transitions {
class GrowEffect : public AbstractTransitionEffect
{
	Q_OBJECT
public:
	explicit GrowEffect(const QPixmap &snapshot, TransitionDirection direction,
						 Qt::Orientation orientation, BoundaryType pinnedBoundary,
						 QObject *parent = nullptr);

	void apply(QPainter *painter, const TransitionOptions &options) override;

private:
	QPixmap _snapshot;
	TransitionDirection _direction;
	Qt::Orientation _orientation;
	BoundaryType _pinnedBoundary;
};
}

#endif // GROWEFFECT_H
