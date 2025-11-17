#include "StillEffect.h"
#include "../TransitionOptions.h"
#include <QPainter>

namespace FlatGui::Cdk::Transitions {
StillEffect::StillEffect(const QPixmap &snapshot, QWidget *parent) :
	AbstractTransitionEffect{parent},
	_snapshot{snapshot}
{

}

void StillEffect::apply(QPainter *painter, const TransitionOptions &options)
{
	painter->drawPixmap(options.rect, _snapshot);
}
}
