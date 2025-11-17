#ifndef DURATIONSCHEME_H
#define DURATIONSCHEME_H

#include "global/flatgui_global.h"
#include "global/FlatGuiEnums.h"
#include <QObject>

namespace FlatGui::Cdk::Transitions {
class DurationSchemePrivate;

class FLATGUI_EXPORT DurationScheme : public QObject
{
	Q_OBJECT
public:
	explicit DurationScheme(QObject *parent = nullptr);
	~DurationScheme();

	int duration(DurationType type) const;
	void setDuration(DurationType type, int value);

private:
	DurationSchemePrivate *_d;
};
}

#endif // DURATIONSCHEME_H
