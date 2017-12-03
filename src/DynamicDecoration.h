#ifndef DYNAMICDECORATION_H
#define DYNAMICDECORATION_H

#include "flatgui_global.h"
#include "AbstractDecoration.h"
#include <QPixmap>

class FLATGUISHARED_EXPORT DynamicDecoration : public AbstractDecoration
{
	Q_OBJECT
public:
	explicit DynamicDecoration(QObject *parent = nullptr);

	void setPixmapOn(const QPixmap &pixmapValid);
	void setPixmapOff(const QPixmap &pixmapInvalid);

	void paint(QPainter *painter) const override;

public slots:
	void setState(bool on);

private:
	QPixmap m_pixmapOn;
	QPixmap m_pixmapOff;

	bool m_on;
};

#endif // DYNAMICDECORATION_H
