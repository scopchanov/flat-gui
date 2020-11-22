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
#include "SidePanel.h"
#include "SSplitView.h"
#include "ToolBar.h"
#include "ToolButton.h"
#include "PushButton.h"
#include "Alert.h"
#include "SimpleMessage.h"
#include "PixmapBuilder.h"
#include <QApplication>
#include <QDesktopServices>
#include <QVBoxLayout>
#include <QLabel>
#include <QUrl>

MainWindow::MainWindow(QWidget *parent) :
	QMainWindow(parent)
{
	auto *widget = new QWidget(this);
	auto *toolBar = new ToolBar(this);
	auto *splitView = new SSplitView(this);
	auto *sidePanel = new SidePanel();
	auto layoutMain = new QVBoxLayout(widget);
	auto *btnMenu = new ToolButton();
	auto *btnAlert = new PushButton();
	auto *btnDrumset = new PushButton();
	auto *labTitle = new QLabel(this);
	auto *labFooter = new QLabel(this);
	auto *labBody = new QLabel(this);

	QPalette p;

	p.setColor(QPalette::Window, QColor("#F0F1F2"));
	p.setColor(QPalette::WindowText, QColor("#303030"));
	p.setColor(QPalette::Base, QColor("#50585D"));
	p.setColor(QPalette::Button, QColor("#FFFFFF"));
	p.setColor(QPalette::Dark, QColor("#50585D"));
	p.setColor(QPalette::Text, QColor("#616b71"));
	p.setColor(QPalette::Highlight, QColor("#15999B"));
	p.setColor(QPalette::Link, QColor("#15999B"));

	QApplication::setPalette(p);
	QApplication::setFont(QFont("MS Shell Dlg 2", 11));

	btnMenu->setPixmap(PixmapBuilder::create(PixmapBuilder::Menu,
											 palette().color(QPalette::Button),
											 16));
	btnMenu->setSize(48);

	labBody->setContentsMargins(12, 12, 12, 12);
	labBody->setWordWrap(true);
	labBody->setAlignment(Qt::AlignLeft | Qt::AlignTop);
	labBody->setText("<p>The FlatGUI library allows Qt5 users to build elegant "
					 "graphical user interfaces for desktop applications in C++ "
					 "without the need of using technologies other than widgets. "
					 "The GUI elements are tested fully under Windows 7/10 and "
					 "partially under Ubuntu 17 Desktop. The library is open "
					 "source and you are welcome to use it and contribute to it.</p>"
					 "<p>Enjoy!</p>"
					 "<p>P.S. I play drums too. Check them out. :)</p>");

	labTitle->setOpenExternalLinks(true);
	labTitle->setText(tr("Created with <a style='text-decoration: none' href='%1'>FlatGUI"
						 "</a> by <a style='text-decoration: none;' href='%2'>Michael "
						 "Scopchanov</a>.")
					  .arg(QStringLiteral("https://github.com/scopchanov/flat-gui"))
					  .arg(QStringLiteral("https://www.xing.com/profile/Michael_Scopchanov/")));

	toolBar->addSpacing(12);
	toolBar->addWidget(labTitle);
	toolBar->addStretch();
	toolBar->addWidget(btnMenu);
	toolBar->setMaximumHeight(48);
	toolBar->setBackgroundRole(QPalette::Dark);

	btnAlert->setText(tr("Show alert"));
	btnDrumset->setText(tr("My drumset"));

	QFont f(font());

	f.setPointSize(10);

	labFooter->setFont(f);
	labFooter->setAlignment(Qt::AlignRight);
	labFooter->setText(tr("Landau/Pfalz<br />"
						  "Germany, 2018"));
	labFooter->setForegroundRole(QPalette::Text);
	labFooter->setStyleSheet(".QLabel { padding: 9px; }");

	sidePanel->addWidget(btnAlert);
	sidePanel->addWidget(btnDrumset);
	sidePanel->addStretch();
	sidePanel->addWidget(labFooter);
	sidePanel->setFixedWidth(150);

	splitView->setBaseWidget(labBody);
	splitView->setSideWidget(sidePanel);
	splitView->setSplitSide(SSplitView::ST_Right);

	layoutMain->addWidget(toolBar);
	layoutMain->addWidget(splitView);
	layoutMain->setContentsMargins(0, 0, 0, 0);
	layoutMain->setSpacing(0);

	setWindowTitle(tr("Side Panel Example"));
	setCentralWidget(widget);
	resize(480, 640);

	connect(btnMenu, &ToolButton::clicked, splitView, &SSplitView::toggleSideWidget);
	connect(btnAlert, &PushButton::clicked, this, &MainWindow::onAlert);
	connect(btnDrumset, &PushButton::clicked, this, &MainWindow::onDrumset);
}

void MainWindow::onAlert()
{
	if (Alert::showAlert(this,
						 PixmapBuilder::create(PixmapBuilder::Warning,
											   palette().color(QPalette::Highlight), 48),
						 tr("This is an alert"),
						 tr("Write text to alert the user<br />"
							"about something and let him/her<br />"
							"decide what to do next."),
						 QStringList({tr("Deny"), tr("Accept")}), 1))
		SimpleMessage::showMessage(this,
								   PixmapBuilder::create(PixmapBuilder::Info,
														 palette().color(QPalette::Highlight), 48),
								   tr("Accepted"), 3000);
	else
		SimpleMessage::showMessage(this,
								   PixmapBuilder::create(PixmapBuilder::Error,
														 palette().color(QPalette::Highlight), 48),
								   tr("Denied"), 3000);
}

void MainWindow::onDrumset()
{
	QDesktopServices::openUrl(QUrl::fromUserInput("https://drums.scopchanov.de/"));
}
