#ifndef SIMPLEMESSAGE_H
#define SIMPLEMESSAGE_H

#include "flatgui_global.h"
#include <QDialog>

class FLATGUISHARED_EXPORT SimpleMessage : public QDialog
{
	Q_OBJECT
public:
	static void showMessage(QWidget *parent, const QPixmap &icon, const QString &message, int timeout);

protected:
	void showEvent(QShowEvent *event) override;

private:
	explicit SimpleMessage(QWidget *parent, const QPixmap &icon, const QString &message, int timeout);

	int m_timeout;

private slots:
	void onTimeout();
};

#endif // SIMPLEMESSAGE_H
