#ifndef LISTITEMANIMATION_H
#define LISTITEMANIMATION_H

#include "flatgui_global.h"
#include <QVariantAnimation>

class QListWidgetItem;

class FLATGUISHARED_EXPORT ListItemAnimation : public QVariantAnimation
{
	Q_OBJECT
public:
	explicit ListItemAnimation(QObject *parent, QListWidgetItem *target);

	QListWidgetItem *target() const;

private:
	QListWidgetItem *m_target;
};

#endif // LISTITEMANIMATION_H
