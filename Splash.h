#ifndef SPLASH_H
#define SPLASH_H

#include "flatgui_global.h"
#include <QSplashScreen>

class FLATGUISHARED_EXPORT Splash : public QSplashScreen
{
	Q_OBJECT
public:
	explicit Splash(const QPixmap &pixmap);

protected:
	void mousePressEvent(QMouseEvent *) override;

signals:
	void splashShown();
};

#endif // SPLASH_H
