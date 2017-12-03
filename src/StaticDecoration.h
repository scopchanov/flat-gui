#ifndef STATICDECORATION_H
#define STATICDECORATION_H

#include "flatgui_global.h"
#include "AbstractDecoration.h"
#include <QPixmap>

class FLATGUISHARED_EXPORT StaticDecoration : public AbstractDecoration
{
	Q_OBJECT
public:
	explicit StaticDecoration(QObject *parent = nullptr);

	void setPixmap(const QPixmap &pixmap);

	void paint(QPainter *painter) const override;

private:
	QPixmap m_pixmap;
};

#endif // STATICDECORATION_H
