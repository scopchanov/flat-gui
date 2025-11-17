#include "BoxWipeComposer.h"
#include "../PageTransition.h"
#include "../effects/BoxEffect.h"
#include "../effects/StillEffect.h"
#include <QEasingCurve>

namespace FlatGui::Cdk::Transitions {
BoxWipeComposer::BoxWipeComposer(QObject *parent) :
	AbstractEffectsComposer{parent}
{

}

void BoxWipeComposer::compose(PageTransition *transition)
{
	if (transition->isForward()) {
		auto *stillA{new StillEffect(transition->snapshotA())};
		auto *boxB{new BoxEffect(transition->snapshotB(), TD_In)};

		transition->addEffect(stillA);
		transition->addEffect(boxB);
		transition->setEasingCurve(QEasingCurve::InQuad);
	} else {
		auto *boxA{new BoxEffect(transition->snapshotA(), TD_Out)};
		auto *stillB{new StillEffect(transition->snapshotB())};

		transition->addEffect(stillB);
		transition->addEffect(boxA);
		transition->setEasingCurve(QEasingCurve::OutQuad);
	}
}
}
