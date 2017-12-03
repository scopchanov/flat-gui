#ifndef SEARCHFORM_H
#define SEARCHFORM_H

#include "flatgui_global.h"
#include <QWidget>

class SearchFormPrivate;

class FLATGUISHARED_EXPORT SearchForm : public QWidget
{
	Q_OBJECT
public:
	explicit SearchForm(QWidget *parent = nullptr);
	~SearchForm();

	QString searchTerm() const;
	int matchType() const;

private:
	SearchFormPrivate *m_ptr;

private slots:
	void onMatchClicked();

signals:
	void contentChanged();
};

#endif // SEARCHFORM_H
