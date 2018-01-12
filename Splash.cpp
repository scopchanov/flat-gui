#include "Splash.h"
#include <QPropertyAnimation>

/*!
 * \class Splash
 * \inmodule FlatGui
 */

Splash::Splash(const QPixmap &pixmap) :
	QSplashScreen(pixmap)
{
	auto *animation = new QPropertyAnimation(this, "windowOpacity", this);

	animation->setStartValue(0.0);
	animation->setEndValue(1.0);
	animation->setDuration(1000);
	animation->setEasingCurve(QEasingCurve::OutQuad);
	animation->start(QPropertyAnimation::DeleteWhenStopped);

	connect(animation, &QPropertyAnimation::finished, this, &Splash::splashShown);
}

void Splash::mousePressEvent(QMouseEvent *)
{

}
