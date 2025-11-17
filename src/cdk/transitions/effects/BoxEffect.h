#ifndef BOXEFFECT_H
#define BOXEFFECT_H

#include "AbstractTransitionEffect.h"
#include "global/FlatGuiEnums.h"

namespace FlatGui::Cdk::Transitions {
class FLATGUI_EXPORT BoxEffect : public AbstractTransitionEffect
{
	Q_OBJECT
public:
	explicit BoxEffect(const QPixmap &snapshot, TransitionDirection direction,
					   QObject *parent = nullptr);

	void apply(QPainter *painter, const TransitionOptions &options) override;

private:
	QPixmap _snapshot;
	TransitionDirection _direction;
};
}

#endif // BOXEFFECT_H
