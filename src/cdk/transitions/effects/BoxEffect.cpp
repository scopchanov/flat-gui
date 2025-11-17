#include "BoxEffect.h"
#include "../TransitionOptions.h"
#include <QPainter>

namespace FlatGui::Cdk::Transitions {
BoxEffect::BoxEffect(const QPixmap &snapshot, TransitionDirection direction,
					 QObject *parent) :
	AbstractTransitionEffect{parent},
	_snapshot{snapshot},
	_direction{direction}
{

}

void BoxEffect::apply(QPainter *painter, const TransitionOptions &options)
{
	const QRect &srcRect{_snapshot.rect()};
	const QRect &dstRect{options.rect};
	bool isForward{options.isForward};
	qreal value{options.value};
	qreal invertedValue{options.invertedValue};
	qreal scale{0.5*(_direction == TD_In
						   ? isForward ? invertedValue : value
						   : isForward ? value : invertedValue)};
	qreal srcW{scale*srcRect.width()};
	qreal srcH{scale*srcRect.height()};
	qreal dstW{scale*dstRect.width()};
	qreal dstH{scale*dstRect.height()};

	painter->drawPixmap(dstRect.adjusted(dstW, dstH, -dstW, -dstH), _snapshot,
						srcRect.adjusted(srcW, srcH, -srcW, -srcH));
}
}
