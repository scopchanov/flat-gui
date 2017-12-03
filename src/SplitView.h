#ifndef SPLITVIEW_H
#define SPLITVIEW_H

#include "flatgui_global.h"
#include <QWidget>

class SplitViewPrivate;

class FLATGUISHARED_EXPORT SplitView : public QWidget
{
	Q_OBJECT
public:
	explicit SplitView(QWidget *parent = nullptr);
	~SplitView();

	void setBaseWidget(QWidget *widget);
	void setSideWidget(QWidget *widget, bool hidden = true);

public slots:
	void splitScreen();

protected:
	void resizeEvent(QResizeEvent *) override;

private:
	SplitViewPrivate *m_ptr;

private slots:
	void onSplitChanged(const QVariant &value);
	void onSplitFinished();
};

#endif // SPLITVIEW_H
