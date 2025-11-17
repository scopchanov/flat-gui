#ifndef SPLITEFFECT_H
#define SPLITEFFECT_H

#include "AbstractTransitionEffect.h"
#include "global/FlatGuiEnums.h"

namespace FlatGui::Cdk::Transitions {
class FLATGUI_EXPORT SplitEffect : public AbstractTransitionEffect
{
	Q_OBJECT
public:
	explicit SplitEffect(const QPixmap &snapshot, Qt::Orientation orientation,
						 TransitionDirection direction, QObject *parent = nullptr);

	void apply(QPainter *painter, const TransitionOptions &options) override;

private:
	QPixmap _snapshot;
	Qt::Orientation _orientation;
	TransitionDirection _direction;
};
}

#endif // SPLITEFFECT_H
