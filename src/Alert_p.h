#ifndef ALERT_P_H
#define ALERT_P_H

class AlertPrivate
{
	explicit AlertPrivate(int defaultButtonIndex);

	int defaultButtonIndex;

	friend class Alert;
};

#endif // ALERT_P_H
