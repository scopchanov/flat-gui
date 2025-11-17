#ifndef CROSSFADECOMPOSER_H
#define CROSSFADECOMPOSER_H

#include "AbstractEffectsComposer.h"

namespace FlatGui::Cdk::Transitions {
class FLATGUI_EXPORT CrossFadeComposer : public AbstractEffectsComposer
{
public:
	explicit CrossFadeComposer(QObject *parent = nullptr);

	void compose(PageTransition *transition) override;
};
}

#endif // CROSSFADECOMPOSER_H
