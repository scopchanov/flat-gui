#ifndef ABSTRACTDECORATION_H
#define ABSTRACTDECORATION_H

#include <QObject>

class QPainter;

class AbstractDecoration : public QObject
{
	Q_OBJECT
public:
	explicit AbstractDecoration(QObject *parent = nullptr);

	virtual void paint(QPainter *painter) const = 0;
};

#endif // ABSTRACTDECORATION_H
