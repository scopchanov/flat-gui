#include "ScaleComposer.h"
#include "../PageTransition.h"
#include "../effects/GrowEffect.h"
#include <QEasingCurve>

namespace FlatGui::Cdk::Transitions {
ScaleComposer::ScaleComposer(QObject *parent) :
	AbstractEffectsComposer{parent}
{

}

void ScaleComposer::compose(PageTransition *transition)
{
	auto orientation{transition->orientation()};
	const QPixmap &snapshotA{transition->snapshotA()};
	const QPixmap &snapshotB{transition->snapshotB()};

	if (transition->isForward()) {
		auto *sizeA{new GrowEffect(snapshotA, TD_Out, orientation, BND_Start)};
		auto *sizeB{new GrowEffect(snapshotB, TD_In, orientation, BND_End)};

		transition->addEffect(sizeA);
		transition->addEffect(sizeB);
		transition->setEasingCurve(QEasingCurve::InQuad);
	} else {
		auto *sizeA{new GrowEffect(snapshotA, TD_Out, orientation, BND_End)};
		auto *sizeB{new GrowEffect(snapshotB, TD_In, orientation, BND_Start)};

		transition->addEffect(sizeA);
		transition->addEffect(sizeB);
		transition->setEasingCurve(QEasingCurve::OutQuad);
	}
}
}
