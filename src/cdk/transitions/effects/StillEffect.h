#ifndef STILLEFFECT_H
#define STILLEFFECT_H

#include "AbstractTransitionEffect.h"

namespace FlatGui::Cdk::Transitions {
class FLATGUI_EXPORT StillEffect : public AbstractTransitionEffect
{
	Q_OBJECT
public:
	explicit StillEffect(const QPixmap &snapshot, QWidget *parent = nullptr);
	
	void apply(QPainter *painter, const TransitionOptions &options) override;

private:
	QPixmap _snapshot;
};
}

#endif // STILLEFFECT_H
