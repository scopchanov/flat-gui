#ifndef TRANSITIONOPTIONS_H
#define TRANSITIONOPTIONS_H

#include "global/flatgui_global.h"

class QRect;

namespace FlatGui::Cdk::Transitions {
class FLATGUI_EXPORT TransitionOptions
{
public:
	qreal value;
	qreal invertedValue;
	bool isForward;
	const QRect &rect;
};
}

#endif // TRANSITIONOPTIONS_H
