#ifndef TRANSITIONMANAGER_H
#define TRANSITIONMANAGER_H

#include "global/flatgui_global.h"
#include "global/FlatGuiEnums.h"
#include <QObject>

namespace FlatGui::Cdk::Transitions {
class TransitionManagerPrivate;
class AbstractEffectsComposer;
class DurationScheme;
class PageTransition;

class FLATGUI_EXPORT TransitionManager : public QObject
{
	Q_OBJECT
public:
	explicit TransitionManager(QObject *parent = nullptr);
	~TransitionManager();

	Qt::Orientation orientation() const;
	void setOrientation(Qt::Orientation orientation);
	AbstractEffectsComposer *effectsComposer() const;
	void setEffectsComposer(AbstractEffectsComposer *composer);

	QWidget *pageA() const;
	void setPageA(QWidget *page);
	QWidget *pageB() const;
	void setPageB(QWidget *page);
	bool isForward() const;
	void setForward(bool forward);

	DurationType durationType() const;
	void setDurationType(DurationType durationType);
	DurationScheme *durationScheme() const;
	bool isBusy() const;

	void start();

private:
	TransitionManagerPrivate *_d;

signals:
	void finished();

	friend class TransitionManagerPrivate;
};
}

#endif // TRANSITIONMANAGER_H
