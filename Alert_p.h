#ifndef ALERT_P_H
#define ALERT_P_H

class Alert;
class QWidget;
class ToolBar;
class QLabel;
class QVBoxLayout;

class AlertPrivate
{
	explicit AlertPrivate(Alert *parent);

	QWidget *body;
	QLabel *labTitle;
	QVBoxLayout *layoutMessage;
	ToolBar *toolBar;
	int defaultButtonIndex;

	friend class Alert;
};

#endif // ALERT_P_H
