#include "Alert.h"
#include "ToolBar.h"
#include "PushButton.h"
#include <QApplication>
#include <QDesktopServices>
#include <QGraphicsDropShadowEffect>
#include <QPropertyAnimation>
#include <QVBoxLayout>
#include <QLabel>
#include <QStyle>
#include <QUrl>

/*!
 * \class Alert
 * \inmodule FlatGui
 */

Alert::Alert(QWidget *parent, const QPixmap &icon, const QString &title, const QString &message, const QStringList &buttonNames, int defaultButtonIndex) :
	QDialog(parent, Qt::FramelessWindowHint),
	m_defaultButtonIndex(defaultButtonIndex)
{
	auto *layoutMain = new QVBoxLayout(this);
	auto *layoutBody = new QVBoxLayout();
	auto *layoutTitle = new QHBoxLayout();
	auto *layoutMessage = new QHBoxLayout();
	auto *effect = new QGraphicsDropShadowEffect(this);
	auto *body = new QWidget(this);
	auto *toolBar = new ToolBar(this);
	auto *labTitle = new QLabel(this);
	auto *labIcon = new QLabel(this);
	auto *labMessage = new QLabel(this);

	labTitle->setText("<b>" + title + "</b>");
	labTitle->setAlignment(Qt::AlignCenter);
	labTitle->setMinimumHeight(48);
	labTitle->setStyleSheet(".QLabel { border: none; border-bottom: 1px solid palette(midlight); }");

	layoutTitle->addWidget(labTitle);
	layoutTitle->setContentsMargins(12, 0, 12, 0);
	layoutTitle->setSpacing(0);

	labIcon->setPixmap(icon);
	labIcon->setAlignment(Qt::AlignLeft | Qt::AlignTop);
	labIcon->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Expanding);

	labMessage->setText(message);
	labMessage->setForegroundRole(QPalette::Text);
	labMessage->setTextInteractionFlags(Qt::LinksAccessibleByMouse | Qt::TextSelectableByMouse);
	labMessage->setTextFormat(Qt::RichText);
	labMessage->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Minimum);
	labMessage->setWordWrap(true);

	layoutMessage->addWidget(labIcon);
	layoutMessage->addWidget(labMessage);
	layoutMessage->setContentsMargins(20, 20, 20, 20);
	layoutMessage->setSpacing(20);

	toolBar->setBackgroundRole(QPalette::Window);
	toolBar->addStretch();

	foreach (const QString &buttonName, buttonNames) {
		auto *button = new PushButton(this);
		int index = buttonNames.indexOf(buttonName);

		button->setText(buttonName);
		button->setDefault(index == defaultButtonIndex);
		button->setProperty("index", index);

		toolBar->addWidget(button);

		connect(button, &PushButton::clicked, this, &Alert::onButtonClicked);
	}

	layoutBody->addLayout(layoutTitle);
	layoutBody->addLayout(layoutMessage);
	layoutBody->addWidget(toolBar);
	layoutBody->setContentsMargins(0, 0, 0, 0);
	layoutBody->setSpacing(0);

	effect->setOffset(0);
	effect->setColor(palette().color(QPalette::Shadow));
	effect->setBlurRadius(5);

	body->setAutoFillBackground(true);
	body->setBackgroundRole(QPalette::Button);
	body->setGraphicsEffect(effect);
	body->setLayout(layoutBody);

	layoutMain->addWidget(body);
	layoutMain->setContentsMargins(10, 10, 10, 10);
	layoutMain->setSpacing(0);

	setAttribute(Qt::WA_TranslucentBackground);
	adjustSize();

	connect(labMessage, &QLabel::linkActivated, this, &Alert::onLinkClicked);
}

int Alert::showAlert(QWidget *parent, const QPixmap &icon, const QString &title, const QString &message, const QStringList &buttonNames, int defaultButtonIndex)
{
	return Alert(parent, icon, title, message, buttonNames, defaultButtonIndex).exec();
}

void Alert::reject()
{
	done(m_defaultButtonIndex);
}

void Alert::showEvent(QShowEvent *event)
{
	if (!parentWidget()) {
		QDialog::showEvent(event);
		return;
	}

	const QRect parentRect(parentWidget()->mapToGlobal(QPoint(0, 0)), parentWidget()->size());
	auto *flyIn = new QPropertyAnimation(this, "pos");

	flyIn->setStartValue(QStyle::alignedRect(Qt::LeftToRight, Qt::AlignHCenter | Qt::AlignBottom, size(), parentRect).topLeft());
	flyIn->setEndValue(QStyle::alignedRect(Qt::LeftToRight, Qt::AlignCenter, size(), parentRect).topLeft());
	flyIn->setDuration(500);
	flyIn->setEasingCurve(QEasingCurve::OutBack);
	flyIn->start(QPropertyAnimation::DeleteWhenStopped);
}

void Alert::onLinkClicked(const QString &link)
{
	if (link == "Qt v5.6.1")
		QApplication::aboutQt();
	else
		QDesktopServices::openUrl(QUrl(link));
}

void Alert::onButtonClicked()
{
	done(sender()->property("index").toInt());
}
