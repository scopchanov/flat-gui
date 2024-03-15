/**
MIT License

Copyright (c) 2020 Michael Scopchanov

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#include "MainWindow.h"
#include "SplitView.h"
#include <QToolButton>
#include <QToolBar>
#include <QLabel>

MainWindow::MainWindow(QWidget *parent) :
	QMainWindow(parent)
{
	auto *toolBar = new QToolBar(this);
	auto *actMenu = new QAction(QIcon(":/pix/images/icons/menu.png"),
								tr("Menu"), this);
	auto *splitView = new SplitView(this);
	auto *labSidePanel = new QLabel(tr("Side Panel"), this);
	auto *labBody = new QLabel("Lorem ipsum dolor sit amet, consetetur sadipscing"
							   " elitr, sed diam nonumy eirmod tempor invidunt ut"
							   " labore et dolore magna aliquyam erat, sed diam"
							   " voluptua. At vero eos et accusam et justo duo"
							   " dolores et ea rebum. Stet clita kasd gubergren,"
							   " no sea takimata sanctus est Lorem ipsum dolor"
							   " sit amet. Lorem ipsum dolor sit amet, consetetur"
							   " sadipscing elitr, sed diam nonumy eirmod tempor"
							   " invidunt ut labore et dolore magna aliquyam erat,"
							   " sed diam voluptua. At vero eos et accusam et"
							   " justo duo dolores et ea rebum. Stet clita kasd"
							   " gubergren, no sea takimata sanctus est Lorem"
							   " ipsum dolor sit amet.", this);

	labSidePanel->setAlignment(Qt::AlignLeft | Qt::AlignTop);
	labSidePanel->setMargin(20);
	labSidePanel->setMinimumWidth(120);

	labBody->setAlignment(Qt::AlignLeft | Qt::AlignTop);
	labBody->setMargin(20);
	labBody->setWordWrap(true);

	toolBar->addAction(actMenu);
	toolBar->setMovable(false);

	splitView->setBaseWidget(labBody);
	splitView->setSideWidget(labSidePanel);
	splitView->closeSideWidget();
	splitView->setSplitSide(SplitView::ST_Left);
	splitView->setSplitDuration(300);

	connect(actMenu, &QAction::triggered, splitView,
			&SplitView::toggleSideWidget);

	setWindowTitle(tr("SplitView Example"));
	setCentralWidget(splitView);
	addToolBar(toolBar);
	resize(480, 400);
}
