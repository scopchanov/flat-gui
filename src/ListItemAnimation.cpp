#include "ListItemAnimation.h"

/*!
 * \class ListItemAnimation
 * \inmodule FlatGui
 */

ListItemAnimation::ListItemAnimation(QObject *parent, QListWidgetItem *target) :
	QVariantAnimation(parent),
	m_target(target)
{

}

QListWidgetItem *ListItemAnimation::target() const
{
	return m_target;
}
