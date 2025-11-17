#ifndef PAGESTACK_H
#define PAGESTACK_H

#include "global/flatgui_global.h"
#include "global/FlatGuiEnums.h"
#include <QWidget>

namespace FlatGui {
namespace Cdk::Transitions {
class AbstractEffectsComposer;
class DurationScheme;
}

namespace Components::Containers {
class PageStackPrivate;

class FLATGUI_EXPORT PageStack : public QWidget
{
	Q_OBJECT
public:
	explicit PageStack(QWidget *parent = nullptr);
	~PageStack();

	QWidget *currentPage() const;
	qsizetype currentIndex() const;
	void setCurrentIndex(qsizetype index);

	void addPage(QWidget *page);
	qsizetype pageCount() const;
	QWidget *pageAt(qsizetype index) const;
	void removePage(QWidget *page);
	void removePageAt(qsizetype index);
	void removePagesToEnd();
	void clear();

	Cdk::Transitions::DurationScheme *durationScheme() const;
	Qt::Orientation orientation() const;
	void setOrientation(Qt::Orientation orientation);
	Cdk::Transitions::AbstractEffectsComposer *effectsComposer() const;
	void setEffectsComposer(Cdk::Transitions::AbstractEffectsComposer *composer);

	void gotoFirstPage();
	void gotoLastPage();
	void gotoPreviousPage();
	void gotoNextPage();
	void gotoPageAt(qsizetype index, DurationType duration);

protected:
	void resizeEvent(QResizeEvent *) override;

private:
	PageStackPrivate *_d;

signals:
	void pageCountChanged();
	void currentPageChanged();
};
}
}

#endif // PAGESTACK_H
