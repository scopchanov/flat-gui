#include "PageStack.h"
#include "PageStack_p.h"
#include "cdk/transitions/TransitionManager.h"

using namespace FlatGui::Cdk::Transitions;

namespace FlatGui::Components::Containers {
PageStack::PageStack(QWidget *parent) :
	QWidget{parent},
	_d{new PageStackPrivate(this)}

{
	setAutoFillBackground(true);
	setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
}

PageStack::~PageStack()
{
	delete _d;
}

QWidget *PageStack::currentPage() const
{
	return _d->currentPage();
}

qsizetype PageStack::currentIndex() const
{
	return _d->currentIndex;
}

void PageStack::setCurrentIndex(qsizetype index)
{
	if (!_d->canSetIndex(index))
		return;

	if (_d->currentPage())
		_d->currentPage()->hide();

	_d->currentIndex = index;
	_d->setupCurrentPage();
}

void PageStack::addPage(QWidget *page)
{
	if (!page || _d->pages.contains(page))
		return;

	page->setParent(this);
	page->hide();

	_d->pages.append(page);

	emit pageCountChanged();
}

qsizetype PageStack::pageCount() const
{
	return _d->pages.count();
}

QWidget *PageStack::pageAt(qsizetype index) const
{
	return _d->isValidIndex(index) ? _d->pages.at(index) : nullptr;
}

void PageStack::removePage(QWidget *page)
{
	if (_d->pages.contains(page))
		removePageAt(_d->pages.indexOf(page));
}

void PageStack::removePageAt(qsizetype index)
{
	if (_d->isTransitionRunning() || !_d->isValidIndex(index))
		return;

	_d->pages.takeAt(index)->deleteLater();

	emit pageCountChanged();

	_d->updateCurrentIndex(index);
}

void PageStack::removePagesToEnd()
{
	if (_d->isTransitionRunning())
		return;

	while (_d->pages.count() - 1 > _d->currentIndex)
		_d->pages.takeLast()->deleteLater();

	emit pageCountChanged();
}

void PageStack::clear()
{
	if (_d->isTransitionRunning())
		return;

	while (_d->pages.count())
		_d->pages.takeLast()->deleteLater();

	emit pageCountChanged();
}

DurationScheme *PageStack::durationScheme() const
{
	return _d->transitionManager->durationScheme();
}

Qt::Orientation PageStack::orientation() const
{
	return _d->transitionManager->orientation();
}

void PageStack::setOrientation(Qt::Orientation orientation)
{
	_d->transitionManager->setOrientation(orientation);
}

AbstractEffectsComposer *PageStack::effectsComposer() const
{
	return _d->transitionManager->effectsComposer();
}

void PageStack::setEffectsComposer(AbstractEffectsComposer *composer)
{
	_d->transitionManager->setEffectsComposer(composer);
}

void PageStack::gotoFirstPage()
{
	gotoPageAt(0, DT_Short);
}

void PageStack::gotoLastPage()
{
	gotoPageAt(_d->pages.count() - 1, DT_Short);
}

void PageStack::gotoPreviousPage()
{
	gotoPageAt(_d->currentIndex - 1, DT_Normal);
}

void PageStack::gotoNextPage()
{
	gotoPageAt(_d->currentIndex + 1, DT_Normal);
}

void PageStack::gotoPageAt(qsizetype index, DurationType duration)
{
	if (!_d->canSetIndex(index))
		return;
	
	_d->isCurrentIndexValid() && _d->transitionManager->effectsComposer()
		? _d->transitionToIndex(index, duration)
		: setCurrentIndex(index);
}

void PageStack::resizeEvent(QResizeEvent *)
{
	auto *currentPage{_d->currentPage()};

	if (currentPage)
		currentPage->resize(size());
}

PageStackPrivate::PageStackPrivate(PageStack *parent) :
	p{parent},
	currentIndex{-1},
	transitionManager{new TransitionManager(parent)}
{
	QObject::connect(transitionManager, &TransitionManager::finished,
					 parent, [this](){
						 onTransitionFinished();
					 });
}

void PageStackPrivate::transitionToIndex(qsizetype index, DurationType duration)
{
	transitionManager->setPageA(pages.at(currentIndex));
	transitionManager->setPageB(pages.at(index));
	transitionManager->setDurationType(duration);
	transitionManager->setForward(index > currentIndex);
	transitionManager->start();
}

void PageStackPrivate::updateCurrentIndex(qsizetype index)
{
	if (index > currentIndex)
		return;

	bool deletedPrevious{index < currentIndex};
	bool deletedLast{currentIndex == pages.count()};

	if (deletedPrevious || deletedLast)
		currentIndex--;

	if (!deletedPrevious)
		setupCurrentPage();
}

void PageStackPrivate::setupCurrentPage()
{
	auto *page{currentPage()};

	if (!page)
		return;

	page->resize(p->size());

	QMetaObject::invokeMethod(page, &QWidget::show, Qt::QueuedConnection);

	emit p->currentPageChanged();
}

QWidget *PageStackPrivate::currentPage() const
{
	return isCurrentIndexValid() ? pages.at(currentIndex) : nullptr;
}

bool PageStackPrivate::canSetIndex(qsizetype index) const
{
	bool isCurrentIndex{index == currentIndex};

	return isValidIndex(index) && !isCurrentIndex && !isTransitionRunning();
}

bool PageStackPrivate::isCurrentIndexValid() const
{
	return isValidIndex(currentIndex);
}

bool PageStackPrivate::isValidIndex(qsizetype index) const
{
	return index >= 0 && index < pages.count();
}

bool PageStackPrivate::isTransitionRunning() const
{
	return transitionManager->isBusy();
}

void PageStackPrivate::onTransitionFinished()
{
	currentIndex = pages.indexOf(transitionManager->pageB());

	emit p->currentPageChanged();
}
}
