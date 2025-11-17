#ifndef BOXWIPECOMPOSER_H
#define BOXWIPECOMPOSER_H

#include "AbstractEffectsComposer.h"

namespace FlatGui::Cdk::Transitions {
class FLATGUI_EXPORT BoxWipeComposer : public AbstractEffectsComposer
{
public:
	explicit BoxWipeComposer(QObject *parent = nullptr);

	void compose(PageTransition *transition) override;
};
}

#endif // BOXWIPECOMPOSER_H
