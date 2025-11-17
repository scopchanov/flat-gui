#ifndef SCALECOMPOSER_H
#define SCALECOMPOSER_H

#include "AbstractEffectsComposer.h"

namespace FlatGui::Cdk::Transitions {
class FLATGUI_EXPORT ScaleComposer : public AbstractEffectsComposer
{
public:
	explicit ScaleComposer(QObject *parent = nullptr);

	void compose(PageTransition *transition) override;
};
}

#endif // SCALECOMPOSER_H
