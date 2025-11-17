#include "SplitComposer.h"
#include "../PageTransition.h"
#include "../effects/StillEffect.h"
#include "../effects/SplitEffect.h"
#include <QEasingCurve>

namespace FlatGui::Cdk::Transitions {
SplitComposer::SplitComposer(QObject *parent) :
	AbstractEffectsComposer{parent}
{

}

void SplitComposer::compose(PageTransition *transition)
{
	auto orientation{transition->orientation()};
	const QPixmap &snapshotA{transition->snapshotA()};
	const QPixmap &snapshotB{transition->snapshotB()};

	if (transition->isForward()) {
		auto *stillA{new StillEffect(snapshotA)};
		auto *splitB{new SplitEffect(snapshotB, orientation, TD_Out)};

		transition->addEffect(stillA);
		transition->addEffect(splitB);
		transition->setEasingCurve(QEasingCurve::OutQuad);
	} else {
		auto *splitA{new SplitEffect(snapshotA, orientation, TD_In)};
		auto *stillB{new StillEffect(snapshotB)};

		transition->addEffect(stillB);
		transition->addEffect(splitA);
		transition->setEasingCurve(QEasingCurve::InQuad);
	}
}
}
