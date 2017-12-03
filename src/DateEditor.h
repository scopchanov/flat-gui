#ifndef DATEEDITOR_H
#define DATEEDITOR_H

#include "AbstractEditor.h"

class MonthView;
class QLabel;

class DateEditor : public AbstractEditor
{
	Q_OBJECT
public:
	explicit DateEditor(QWidget *parent = nullptr);

	QDate date() const;
	void setDate(const QDate &date);

public slots:
	void reposition() override;

private:
	MonthView *m_view;
	QLabel *m_labTitle;

private slots:
	void onDateChanged(const QDate &);
};

#endif // DATEEDITOR_H
