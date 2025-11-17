#include "SlideComposer.h"
#include "../PageTransition.h"
#include "../effects/MoveEffect.h"
#include "../effects/StillEffect.h"
#include <QEasingCurve>

namespace FlatGui::Cdk::Transitions {
SlideComposer::SlideComposer(QObject *parent) :
	AbstractEffectsComposer{parent}
{

}

void SlideComposer::compose(PageTransition *transition)
{
	auto orientation{transition->orientation()};
	auto *drawA{new StillEffect(transition->snapshotA())};
	auto *slideB{new MoveEffect(transition->snapshotB(), TD_In, orientation)};

	transition->addEffect(drawA);
	transition->addEffect(slideB);
	transition->setEasingCurve(QEasingCurve::InOutQuad);
}
}
