#ifndef ALERT_H
#define ALERT_H

#include "flatgui_global.h"
#include <QDialog>

class AlertPrivate;

class FLATGUISHARED_EXPORT Alert : public QDialog
{
	Q_OBJECT
public:
	explicit Alert(QWidget *parent = nullptr);
	~Alert();

	void setTitle(const QString &title);
	void setWidget(QWidget *widget);
	void setButtons(const QStringList &buttonNames, int defaultButtonIndex = 0);

	QWidget *body() const;

	static int showAlert(QWidget *parent, const QPixmap &icon, const QString &title, const QString &message, const QStringList &buttonNames, int defaultButtonIndex);

	void reject();

protected:
	void showEvent(QShowEvent *event) override;

private:
	explicit Alert(QWidget *parent, QWidget *widget);

	AlertPrivate *m_ptr;

private slots:
	void onButtonClicked();
};

#endif // ALERT_H
