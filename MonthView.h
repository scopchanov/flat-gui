#ifndef MONTHVIEW_H
#define MONTHVIEW_H

#include "MonthPage.h"

class FLATGUISHARED_EXPORT MonthView : public QWidget
{
	Q_OBJECT
public:
	explicit MonthView(QWidget *parent = nullptr);

	QString title() const;
	QDate date() const;
	void setDate(const QDate &date);

protected:
	void resizeEvent(QResizeEvent *) override;

public slots:
	void onDecClicked();
	void onIncClicked();

private:
	void slide(bool left);

	MonthPage *m_page;
	bool m_transitionInProgress;

private slots:
	void onSlideFinished();

signals:
	void monthChanged(const QString &);
	void dateChanged(const QDate &);
};

#endif // MONTHVIEW_H
