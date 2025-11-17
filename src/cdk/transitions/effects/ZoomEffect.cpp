#include "ZoomEffect.h"
#include "../TransitionOptions.h"
#include <QPainter>

namespace FlatGui::Cdk::Transitions {
ZoomEffect::ZoomEffect(const QPixmap &snapshot, TransitionDirection direction,
					   QObject *parent) :
	AbstractTransitionEffect{parent},
	_snapshot{snapshot},
	_direction{direction}
{

}

void ZoomEffect::apply(QPainter *painter, const TransitionOptions &options)
{
	const QRect &rect{options.rect};
	bool isForward{options.isForward};
	qreal value{options.value};
	qreal invertedValue{options.invertedValue};
	qreal scale{0.5*(_direction == TD_In
						   ? isForward ? invertedValue : value
						   : isForward ? value : invertedValue)};
	qreal dw{scale*rect.width()};
	qreal dh{scale*rect.height()};

	painter->drawPixmap(rect.adjusted(dw, dh, -dw, -dh), _snapshot);
}
}
