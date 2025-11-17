#ifndef PUSHCOMPOSER_H
#define PUSHCOMPOSER_H

#include "AbstractEffectsComposer.h"

namespace FlatGui::Cdk::Transitions {
class FLATGUI_EXPORT PushComposer : public AbstractEffectsComposer
{
public:
	explicit PushComposer(QObject *parent = nullptr);

	void compose(PageTransition *transition) override;
};
}

#endif // PUSHCOMPOSER_H
