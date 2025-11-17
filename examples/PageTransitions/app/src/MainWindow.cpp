#include "MainWindow.h"
#include "FileHandler.h"
#include "Page.h"
#include <cdk/transitions/composers/BoxWipeComposer.h>
#include <cdk/transitions/composers/CrossFadeComposer.h>
#include <cdk/transitions/composers/PushComposer.h>
#include <cdk/transitions/composers/ScaleComposer.h>
#include <cdk/transitions/composers/SlideComposer.h>
#include <cdk/transitions/composers/SplitComposer.h>
#include <cdk/transitions/composers/ZoomComposer.h>
#include <cdk/transitions/DurationScheme.h>
#include <components/containers/PageStack.h>
#include <QJsonObject>
#include <QJsonArray>
#include <QScrollArea>
#include <QToolBar>
#include <QAction>
#include <QLabel>

using namespace FlatGui::Components::Containers;
using namespace FlatGui::Cdk::Transitions;

MainWindow::MainWindow(QWidget *parent) :
	QMainWindow(parent),
	_pageStack{new PageStack(this)},
	_actPrevious{createAction("arrow-left", tr("Previous"))},
	_actNext{createAction("arrow-right", tr("Next"))},
	_labTitle{new QLabel(this)}
{
	const QJsonObject &json{FileHandler::readContent(":/txt/content.json")};
	const QJsonArray &pages{json.value("pages").toArray()};

	// ***********************************
	// Uncomment one of the transition composers below to test it.
	auto *composer{new BoxWipeComposer()};
	// auto *composer{new CrossFadeComposer()};
	// auto *composer{new PushComposer()};
	// auto *composer{new ScaleComposer()};
	// auto *composer{new SlideComposer()};
	// auto *composer{new SplitComposer()};
	// auto *composer{new ZoomComposer()};

	auto *toolBar{new QToolBar(this)};

	toolBar->addAction(_actPrevious);
	toolBar->addWidget(createStretch());
	toolBar->addWidget(_labTitle);
	toolBar->addWidget(createStretch());
	toolBar->addAction(_actNext);
	toolBar->setMovable(false);
	toolBar->setIconSize(QSize(32, 32));

	for (const auto &page : pages)
		_pageStack->addPage(createPage(page.toObject()));

	_pageStack->setCurrentIndex(0);

	// ***********************************
	// Some transitions have orientation. Uncomment the next line to test it.
	// _pageStack->setOrientation(Qt::Vertical);

	_pageStack->durationScheme()->setDuration(FlatGui::DT_Normal, 500);
	_pageStack->setEffectsComposer(composer);

	updateToolbar();
	setWindowTitle(tr("Page Transitions Example"));
	addToolBar(toolBar);
	setCentralWidget(_pageStack);
	resize(480, 640);

	connect(_actPrevious, &QAction::triggered, _pageStack, &PageStack::gotoPreviousPage);
	connect(_actNext, &QAction::triggered, _pageStack, &PageStack::gotoNextPage);
	connect(_pageStack, &PageStack::currentPageChanged, this, &MainWindow::updateToolbar);
	connect(_pageStack, &PageStack::pageCountChanged, this, &MainWindow::updateToolbar);
}

QWidget *MainWindow::createPage(const QJsonObject &json)
{
	auto *scrollArea{new QScrollArea(this)};
	auto *page{new Page()};
	const QString &title{json.value("title").toString()};

	page->setWindowTitle(title);
	page->setText(json.value("text").toString());
	page->setImage(QPixmap(":/pix/images/photos/" + json.value("image").toString()));

	scrollArea->setAlignment(Qt::AlignTop | Qt::AlignLeft);
	scrollArea->setWidget(page);
	scrollArea->setWidgetResizable(true);
	scrollArea->setWindowTitle(title);
	scrollArea->setFrameStyle(QFrame::NoFrame);

	return scrollArea;
}

QAction *MainWindow::createAction(const QString &iconName, const QString &text)
{
	const QIcon &icon{QIcon(":/pix/images/icons/48/" + iconName  + ".png")};

	return new QAction(icon, text, this);
}

QWidget *MainWindow::createStretch()
{
	auto *stretch{new QWidget(this)};

	stretch->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Preferred);

	return stretch;
}

void MainWindow::updateToolbar()
{
	qsizetype currentIndex{_pageStack->currentIndex()};

	_actPrevious->setEnabled(currentIndex > 0);
	_actNext->setEnabled(currentIndex < _pageStack->pageCount() - 1);
	_labTitle->setText(_pageStack->currentPage()->windowTitle());
}
