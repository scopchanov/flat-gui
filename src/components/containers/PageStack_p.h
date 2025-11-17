#ifndef PAGESTACK_P_H
#define PAGESTACK_P_H

#include <QtCore/qglobal.h>
#include <QList>
#include "global/FlatGuiEnums.h"

class QWidget;

namespace FlatGui {
namespace Cdk::Transitions {
class TransitionManager;
}

namespace Components::Containers {
class PageStack;

class PageStackPrivate
{
	Q_DISABLE_COPY(PageStackPrivate)

	explicit PageStackPrivate(PageStack *parent);

	void transitionToIndex(qsizetype index, DurationType duration);
	void updateCurrentIndex(qsizetype index);
	void setupCurrentPage();
	QWidget *currentPage() const;
	bool canSetIndex(qsizetype index) const;
	bool isCurrentIndexValid() const;
	bool isValidIndex(qsizetype index) const;
	bool isTransitionRunning() const;
	void onTransitionFinished();

	PageStack *p;
	QList<QWidget *> pages;
	qsizetype currentIndex;
	Cdk::Transitions::TransitionManager *transitionManager;

	friend class PageStack;
};
}
}

#endif // PAGESTACK_P_H
