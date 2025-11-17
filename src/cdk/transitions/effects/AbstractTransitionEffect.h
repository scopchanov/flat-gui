#ifndef ABSTRACTTRANSITIONEFFECT_H
#define ABSTRACTTRANSITIONEFFECT_H

#include "global/flatgui_global.h"
#include <QWidget>

class QPainter;

namespace FlatGui::Cdk::Transitions {
class TransitionOptions;

class FLATGUI_EXPORT AbstractTransitionEffect : public QObject
{
	Q_OBJECT
public:
	explicit AbstractTransitionEffect(QObject *parent = nullptr);

	virtual void apply(QPainter *painter, const TransitionOptions &options) = 0;
};
}

#endif // ABSTRACTTRANSITIONEFFECT_H
