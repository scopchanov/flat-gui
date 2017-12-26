#ifndef ALERT_P_H
#define ALERT_P_H

class Alert;
class ToolBar;
class QLabel;
class QVBoxLayout;

class AlertPrivate
{
	explicit AlertPrivate(Alert *parent);

	QLabel *labTitle;
	QVBoxLayout *layoutMessage;
	ToolBar *toolBar;
	int defaultButtonIndex;

	friend class Alert;
};

#endif // ALERT_P_H
