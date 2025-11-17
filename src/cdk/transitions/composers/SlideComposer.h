#ifndef SLIDECOMPOSER_H
#define SLIDECOMPOSER_H

#include "AbstractEffectsComposer.h"

namespace FlatGui::Cdk::Transitions {
class FLATGUI_EXPORT SlideComposer : public AbstractEffectsComposer
{
public:
	explicit SlideComposer(QObject *parent = nullptr);

	void compose(PageTransition *transition) override;
};
}

#endif // SLIDECOMPOSER_H
