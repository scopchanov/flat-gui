#ifndef ZOOMCOMPOSER_H
#define ZOOMCOMPOSER_H

#include "AbstractEffectsComposer.h"

namespace FlatGui::Cdk::Transitions {
class FLATGUI_EXPORT ZoomComposer : public AbstractEffectsComposer
{
public:
	explicit ZoomComposer(QObject *parent = nullptr);

	void compose(PageTransition *transition) override;
};
}

#endif // ZOOMCOMPOSER_H
