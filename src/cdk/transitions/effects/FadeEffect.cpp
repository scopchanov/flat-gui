#include "FadeEffect.h"
#include "../TransitionOptions.h"
#include <QPainter>

namespace FlatGui::Cdk::Transitions {
FadeEffect::FadeEffect(TransitionDirection direction, QWidget *parent) :
	AbstractTransitionEffect{parent},
	_direction{direction}
{

}

void FadeEffect::apply(QPainter *painter, const TransitionOptions &options)
{
	bool isForward{options.isForward};
	qreal value{options.value};
	qreal invertedValue{options.invertedValue};
	qreal opacity{_direction == TD_In
					  ? isForward ? value : invertedValue
					  : isForward ? invertedValue : value};

	painter->setOpacity(opacity);
}
}
