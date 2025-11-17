#include "CrossFadeComposer.h"
#include "../PageTransition.h"
#include "../effects/FadeEffect.h"
#include "../effects/StillEffect.h"

namespace FlatGui::Cdk::Transitions {
CrossFadeComposer::CrossFadeComposer(QObject *parent) :
	AbstractEffectsComposer{parent}
{

}

void CrossFadeComposer::compose(PageTransition *transition)
{
	transition->addEffect(new FadeEffect(TD_Out));
	transition->addEffect(new StillEffect(transition->snapshotA()));
	transition->addEffect(new FadeEffect(TD_In));
	transition->addEffect(new StillEffect(transition->snapshotB()));
}
}
