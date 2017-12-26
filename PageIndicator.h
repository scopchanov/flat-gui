#ifndef PAGEINDICATOR_H
#define PAGEINDICATOR_H

#include "flatgui_global.h"
#include <QWidget>

class QHBoxLayout;

class FLATGUISHARED_EXPORT PageIndicator : public QWidget
{
	Q_OBJECT
public:
	explicit PageIndicator(QWidget *parent = nullptr);

	void setPixmapActive(const QPixmap &pixmap);
	void setPixmapInactive(const QPixmap &pixmap);

public slots:
	void setCount(int cnt);
	void setCurrentIndex(int n, int);

private:
	QHBoxLayout *m_layoutDots;
	QPixmap m_pixmapActive;
	QPixmap m_pixmapInactive;
};

#endif // PAGEINDICATOR_H
