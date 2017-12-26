#ifndef SPLASH_H
#define SPLASH_H

#include "flatgui_global.h"
#include <QSplashScreen>

class FLATGUISHARED_EXPORT Splash : public QSplashScreen
{
	Q_OBJECT
public:
	explicit Splash(const QPixmap &pixmap);

	bool isReady() const;

private:
	bool m_ready;

private slots:
	void onAnimationFinished();
};

#endif // SPLASH_H
