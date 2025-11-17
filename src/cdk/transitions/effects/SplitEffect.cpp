#include "SplitEffect.h"
#include "../TransitionOptions.h"
#include <QPainter>

namespace FlatGui::Cdk::Transitions {
SplitEffect::SplitEffect(const QPixmap &snapshot, Qt::Orientation orientation,
						 TransitionDirection direction, QObject *parent) :
	AbstractTransitionEffect{parent},
	_snapshot{snapshot},
	_orientation{orientation},
	_direction{direction}
{

}

void SplitEffect::apply(QPainter *painter, const TransitionOptions &options)
{
	const QRect &srcRect{_snapshot.rect()};
	const QRect &dstRect{options.rect};
	bool isForward{options.isForward};
	bool isHorizontal{_orientation == Qt::Horizontal};
	qreal value{options.value};
	qreal invertedValue{options.invertedValue};
	qreal scale{0.5*(_direction == TD_In
						   ? isForward ? value : invertedValue
						   : isForward ? invertedValue : value)};
	qreal srcW{isHorizontal ? scale*srcRect.width() : 0};
	qreal srcH{isHorizontal ? 0 : scale*srcRect.height()};
	qreal dstW{isHorizontal ? scale*dstRect.width() : 0};
	qreal dstH{isHorizontal ? 0 : scale*dstRect.height()};

	painter->drawPixmap(dstRect.adjusted(dstW, dstH, -dstW, -dstH), _snapshot,
						srcRect.adjusted(srcW, srcH, -srcW, -srcH));
}
}
