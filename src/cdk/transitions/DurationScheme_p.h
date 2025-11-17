#ifndef DURATIONSCHEME_P_H
#define DURATIONSCHEME_P_H

#include <QtCore/qglobal.h>
#include <QList>

namespace FlatGui::Cdk::Transitions {
class DurationSchemePrivate
{
	Q_DISABLE_COPY(DurationSchemePrivate)

	explicit DurationSchemePrivate();

	QList<int> durations;

	friend class DurationScheme;
};
}

#endif // DURATIONSCHEME_P_H
