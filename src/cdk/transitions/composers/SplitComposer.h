#ifndef SPLITCOMPOSER_H
#define SPLITCOMPOSER_H

#include "AbstractEffectsComposer.h"

namespace FlatGui::Cdk::Transitions {
class FLATGUI_EXPORT SplitComposer : public AbstractEffectsComposer
{
public:
	explicit SplitComposer(QObject *parent = nullptr);

	void compose(PageTransition *transition) override;
};
}

#endif // SPLITCOMPOSER_H
