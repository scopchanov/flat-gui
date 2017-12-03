#ifndef GRIDWIDGET_H
#define GRIDWIDGET_H

#include <QWidget>

class GridWidgetPrivate;
class ButtonCategory;

class GridWidget : public QWidget
{
	Q_OBJECT
public:
	explicit GridWidget(QWidget *parent = nullptr);
	~GridWidget();

	void setDescription(const QString &text);
	ButtonCategory *createButton(const QString &name, const QString &description, const QPixmap &pixmap, QAction *act);

protected:
	void resizeEvent(QResizeEvent *) override;
	QSize minimumSizeHint() const override;

private:
	GridWidgetPrivate *m_ptr;
};

#endif // GRIDWIDGET_H
