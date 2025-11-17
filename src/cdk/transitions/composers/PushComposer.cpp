#include "PushComposer.h"
#include "../PageTransition.h"
#include "../effects/MoveEffect.h"
#include <QEasingCurve>

namespace FlatGui::Cdk::Transitions {
PushComposer::PushComposer(QObject *parent) :
	AbstractEffectsComposer{parent}
{

}

void PushComposer::compose(PageTransition *transition)
{
	auto orientation{transition->orientation()};
	auto *slideA{new MoveEffect(transition->snapshotA(), TD_Out, orientation)};
	auto *slideB{new MoveEffect(transition->snapshotB(), TD_In, orientation)};

	transition->addEffect(slideA);
	transition->addEffect(slideB);
	transition->setEasingCurve(QEasingCurve::InOutQuad);
}
}
