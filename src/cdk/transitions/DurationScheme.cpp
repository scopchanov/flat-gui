#include "DurationScheme.h"
#include "DurationScheme_p.h"

namespace FlatGui::Cdk::Transitions {
DurationScheme::DurationScheme(QObject *parent) :
	QObject{parent},
	_d{new DurationSchemePrivate()}
{

}

DurationScheme::~DurationScheme()
{
	delete _d;
}

int DurationScheme::duration(DurationType type) const
{
	return _d->durations.at(type);
}

void DurationScheme::setDuration(DurationType type, int value)
{
	_d->durations[type] = value;
}

DurationSchemePrivate::DurationSchemePrivate()
{
	durations.append(1000);
	durations.append(500);
	durations.append(250);
}
}
