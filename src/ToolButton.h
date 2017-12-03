#ifndef TOOLBUTTON_H
#define TOOLBUTTON_H

#include "AbstractButton.h"

class ToolButtonPrivate;

class FLATGUISHARED_EXPORT ToolButton : public AbstractButton
{
	Q_OBJECT
public:
	explicit ToolButton(QWidget *parent = nullptr);
	~ToolButton();

	void setPixmap(const QPixmap &pixmap);
	virtual void setSize(int n);

protected:
	void paintEvent(QPaintEvent *event) override final;

	virtual void paint(QPainter *painter);
	void setPixmapOrigin(const QPoint &p);
	void setScaleFactor(qreal d);

private:
	ToolButtonPrivate *m_ptr;
};

#endif // TOOLBUTTON_H
