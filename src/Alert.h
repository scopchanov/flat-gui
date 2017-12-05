#ifndef ALERT_H
#define ALERT_H

#include "flatgui_global.h"
#include <QDialog>

class AlertPrivate;

class FLATGUISHARED_EXPORT Alert : public QDialog
{
	Q_OBJECT
public:
	static int showAlert(QWidget *parent, const QPixmap &icon, const QString &title, const QString &message, const QStringList &buttonNames, int defaultButtonIndex);
	static int aboutQt(QWidget *parent);

	void reject();

protected:
	void showEvent(QShowEvent *event) override;

private:
	explicit Alert(QWidget *parent, const QPixmap &icon, const QString &title, const QString &message, const QStringList &buttonNames, int defaultButtonIndex);
	explicit Alert(QWidget *parent);
	~Alert();

	AlertPrivate *m_ptr;

private slots:
	void onLinkClicked(const QString &link);
	void onButtonClicked();
};

#endif // ALERT_H
