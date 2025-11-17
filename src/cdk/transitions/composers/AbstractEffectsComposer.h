#ifndef ABSTRACTEFFECTSCOMPOSER_H
#define ABSTRACTEFFECTSCOMPOSER_H

#include "global/flatgui_global.h"
#include <QObject>

namespace FlatGui::Cdk::Transitions {
class PageTransition;

class FLATGUI_EXPORT AbstractEffectsComposer : public QObject
{
	Q_OBJECT
public:
	explicit AbstractEffectsComposer(QObject *parent = nullptr);

	virtual void compose(PageTransition *transition) = 0;
};
}

#endif // ABSTRACTEFFECTSCOMPOSER_H
