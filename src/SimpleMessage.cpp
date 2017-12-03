#include "SimpleMessage.h"
#include "ToolButton.h"
#include "PixmapBuilder.h"
#include <QGraphicsDropShadowEffect>
#include <QVBoxLayout>
#include <QLabel>
#include <QStyle>
#include <QPropertyAnimation>
#include <QTimer>

/*!
 * \class SimpleMessage
 * \inmodule FlatGui
 */

void SimpleMessage::showMessage(QWidget *parent, const QPixmap &icon, const QString &message, int timeout)
{
	SimpleMessage(parent, icon, message, timeout).exec();
}

void SimpleMessage::showEvent(QShowEvent *event)
{
	if (!parentWidget()) {
		QDialog::showEvent(event);
		return;
	}

	const QRect parentRect(parentWidget()->mapToGlobal(QPoint(0, 0)), parentWidget()->size());
	auto *flyIn = new QPropertyAnimation(this, "pos");
	auto *timer = new QTimer(this);

	timer->setSingleShot(true);
	timer->setInterval(m_timeout);

	flyIn->setStartValue(QStyle::alignedRect(Qt::LeftToRight, Qt::AlignHCenter | Qt::AlignBottom, size(), parentRect).topLeft());
	flyIn->setEndValue(QStyle::alignedRect(Qt::LeftToRight, Qt::AlignCenter, size(), parentRect).topLeft());
	flyIn->setDuration(500);
	flyIn->setEasingCurve(QEasingCurve::OutBack);
	flyIn->start(QPropertyAnimation::DeleteWhenStopped);

	connect(flyIn, &QPropertyAnimation::finished, timer, static_cast<void (QTimer::*)(void)>(&QTimer::start));
	connect(timer, &QTimer::timeout, this, &SimpleMessage::onTimeout);
}

SimpleMessage::SimpleMessage(QWidget *parent, const QPixmap &icon, const QString &message, int timeout) :
	QDialog(parent, Qt::FramelessWindowHint),
	m_timeout(timeout)
{
	auto *layoutMain = new QVBoxLayout(this);
	auto *layoutBody = new QHBoxLayout();
	auto *body = new QWidget(this);
	auto *effect = new QGraphicsDropShadowEffect(this);
	auto *labIcon = new QLabel(this);
	auto *labMessage = new QLabel(message, this);
	auto *btnClose = new ToolButton(this);

	labIcon->setPixmap(icon);
	labIcon->setAlignment(Qt::AlignLeft | Qt::AlignTop);
	labIcon->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
	labIcon->setContentsMargins(12, 12, 12, 12);

	labMessage->setWordWrap(true);
	labMessage->setAlignment(Qt::AlignCenter);

	btnClose->setPixmap(PixmapBuilder::create(PixmapBuilder::Cross, palette().color(QPalette::Mid)));
	btnClose->setSize(32);

	layoutBody->addWidget(labIcon);
	layoutBody->addWidget(labMessage);
	layoutBody->addWidget(btnClose);
	layoutBody->setAlignment(btnClose, Qt::AlignRight | Qt::AlignTop);
	layoutBody->setContentsMargins(0, 0, 0, 0);
	layoutBody->setSpacing(12);

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

	connect(btnClose, &ToolButton::clicked, this, &SimpleMessage::accept);
}

void SimpleMessage::onTimeout()
{
	auto *fadeOut = new QPropertyAnimation(this, "windowOpacity");

	fadeOut->setStartValue(1.0);
	fadeOut->setEndValue(0.0);
	fadeOut->setDuration(150);
	fadeOut->start(QPropertyAnimation::DeleteWhenStopped);

	connect(fadeOut, &QPropertyAnimation::finished, this, &SimpleMessage::accept);
}
