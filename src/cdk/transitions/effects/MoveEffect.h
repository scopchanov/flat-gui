#ifndef MOVEEFFECT_H
#define MOVEEFFECT_H

#include "AbstractTransitionEffect.h"
#include "global/FlatGuiEnums.h"

namespace FlatGui::Cdk::Transitions {
class FLATGUI_EXPORT MoveEffect : public AbstractTransitionEffect
{
	Q_OBJECT
public:
	explicit MoveEffect(const QPixmap &snapshot, TransitionDirection direction,
						   Qt::Orientation orientation, QObject *parent = nullptr);

	void apply(QPainter *painter, const TransitionOptions &options) override;

private:
	QPixmap _snapshot;
	TransitionDirection _direction;
	Qt::Orientation _orientation;
};
}

#endif // MOVEEFFECT_H
