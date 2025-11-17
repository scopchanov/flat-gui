#include "GrowEffect.h"
#include "../TransitionOptions.h"
#include <QPainter>

namespace FlatGui::Cdk::Transitions {
GrowEffect::GrowEffect(const QPixmap &snapshot, TransitionDirection direction,
						 Qt::Orientation orientation, BoundaryType pinnedBoundary,
						 QObject *parent) :
	AbstractTransitionEffect{parent},
	_snapshot{snapshot},
	_direction{direction},
	_orientation{orientation},
	_pinnedBoundary{pinnedBoundary}
{

}

void GrowEffect::apply(QPainter *painter, const TransitionOptions &options)
{
	const QRect &rect{options.rect};
	bool isForward{options.isForward};
	bool isHorizontal{_orientation == Qt::Horizontal};
	bool isStartPinned{_pinnedBoundary == BND_Start};
	qreal value{options.value};
	qreal invertedValue{options.invertedValue};
	qreal scale{_direction == TD_In
					? isForward ? invertedValue : value
					: isForward ? value : invertedValue};
	qreal dw{isHorizontal ? scale*rect.width() : 0};
	qreal dh{isHorizontal ? 0 : scale*rect.height()};
	qreal x1{isStartPinned ? 0 : dw};
	qreal y1{isStartPinned ? 0 : dh};
	qreal x2{isStartPinned ? -dw : 0};
	qreal y2{isStartPinned ? -dh : 0};

	painter->drawPixmap(rect.adjusted(x1, y1, x2, y2), _snapshot);
}
}
