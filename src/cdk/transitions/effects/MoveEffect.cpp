#include "MoveEffect.h"
#include "../TransitionOptions.h"
#include <QPainter>

namespace FlatGui::Cdk::Transitions {
MoveEffect::MoveEffect(const QPixmap &snapshot, TransitionDirection direction,
							 Qt::Orientation orientation, QObject *parent) :
	AbstractTransitionEffect{parent},
	_snapshot{snapshot},
	_direction{direction},
	_orientation{orientation}
{

}

void MoveEffect::apply(QPainter *painter, const TransitionOptions &options)
{
	const QRect &rect{options.rect};
	bool isHorizontal{_orientation == Qt::Horizontal};
	bool isForward{options.isForward};
	int length{isHorizontal ? rect.width() : rect.height()};
	qreal value{options.value};
	qreal invertedValue{options.invertedValue};
	qreal normalizedOffset{_direction == TD_In
							   ? isForward ? invertedValue : -value
							   : isForward ? -value : invertedValue};
	qreal offset{normalizedOffset * length};
	qreal dx{isHorizontal ? offset : 0};
	qreal dy{isHorizontal ? 0 : offset};

	painter->drawPixmap(rect.translated(dx, dy), _snapshot);
}
}
