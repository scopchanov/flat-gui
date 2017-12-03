#ifndef SLIDEVIEW_H
#define SLIDEVIEW_H

#include "flatgui_global.h"
#include <QWidget>

class SlideViewPrivate;

class FLATGUISHARED_EXPORT SlideView : public QWidget
{
	Q_OBJECT
public:
	explicit SlideView(QWidget *parent = nullptr);
	~SlideView();

	void addHomePage(QWidget *page);
	void addPage(QWidget *page, bool dontStack = true);

public slots:
	void gotoPreviousPage();
	void gotoFirstPage();
	void gotoNextPage();
	void gotoPage(int n);

protected:
	void resizeEvent(QResizeEvent *) override;

private:
	SlideViewPrivate *m_ptr;

signals:
	void countChanged(int);
	void currentIndexChanged(int, int);
	void currentPageChanged(const QString &);
};

#endif // SLIDEVIEW_H
