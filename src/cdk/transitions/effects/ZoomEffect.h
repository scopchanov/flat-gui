#ifndef ZOOMEFFECT_H
#define ZOOMEFFECT_H

#include "AbstractTransitionEffect.h"
#include "global/FlatGuiEnums.h"

namespace FlatGui::Cdk::Transitions {
class FLATGUI_EXPORT ZoomEffect : public AbstractTransitionEffect
{
	Q_OBJECT
public:
	explicit ZoomEffect(const QPixmap &snapshot, TransitionDirection direction,
						QObject *parent = nullptr);

	void apply(QPainter *painter, const TransitionOptions &options) override;

private:
	QPixmap _snapshot;
	TransitionDirection _direction;
};
}

#endif // ZOOMEFFECT_H
