#ifndef SPLITVIEW_H
#define SPLITVIEW_H

#include "flatgui_global.h"
#include <QWidget>

class SplitViewPrivate;

class FLATGUISHARED_EXPORT SplitView : public QWidget
{
	Q_OBJECT
public:
	enum SideType : int {
		ST_Left,
		ST_Right
	};

	explicit SplitView(QWidget *parent = nullptr);
	~SplitView();

	void setBaseWidget(QWidget *widget);
	void setSideWidget(QWidget *widget, bool hidden = true);
	SideType splitSide() const;
	void setSplitSide(SideType sd);

public slots:
	void toggleSideWidget();

protected:
	void resizeEvent(QResizeEvent *) override;

private:
	SplitViewPrivate *m_ptr;

private slots:
	void onValueChanged(const QVariant &value);
	void onAnimationFinished();

signals:
	void toggled(bool isOpen);
};

#endif // SPLITVIEW_H
