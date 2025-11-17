#include "ZoomComposer.h"
#include "../PageTransition.h"
#include "../effects/StillEffect.h"
#include "../effects/ZoomEffect.h"
#include <QEasingCurve>

namespace FlatGui::Cdk::Transitions {
ZoomComposer::ZoomComposer(QObject *parent) :
	AbstractEffectsComposer{parent}
{

}

void ZoomComposer::compose(PageTransition *transition)
{
	const QPixmap &snapshotA{transition->snapshotA()};
	const QPixmap &snapshotB{transition->snapshotB()};

	if (transition->isForward()) {
		auto *zoomOutA{new ZoomEffect(snapshotA, TD_Out)};
		auto *stillB{new StillEffect(snapshotB)};

		transition->addEffect(stillB);
		transition->addEffect(zoomOutA);
		transition->setEasingCurve(QEasingCurve::InQuad);
	} else {
		auto *stillA{new StillEffect(snapshotA)};
		auto *zoomInB{new ZoomEffect(snapshotB, TD_In)};

		transition->addEffect(stillA);
		transition->addEffect(zoomInB);
		transition->setEasingCurve(QEasingCurve::OutQuad);
	}
}
}
