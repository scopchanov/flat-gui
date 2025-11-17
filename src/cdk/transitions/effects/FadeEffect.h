#ifndef FADEEFFECT_H
#define FADEEFFECT_H

#include "AbstractTransitionEffect.h"
#include "global/FlatGuiEnums.h"

namespace FlatGui::Cdk::Transitions {
class FLATGUI_EXPORT FadeEffect : public AbstractTransitionEffect
{
	Q_OBJECT
public:
	explicit FadeEffect(TransitionDirection direction, QWidget *parent = nullptr);

	void apply(QPainter *painter, const TransitionOptions &options) override;

private:
	TransitionDirection _direction;
};
}

#endif // FADEEFFECT_H
