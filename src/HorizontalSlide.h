#ifndef HORIZONTALSLIDE_H
#define HORIZONTALSLIDE_H

#include <QObject>

class QLabel;

class HorizontalSlide : public QObject
{
	Q_OBJECT
public:
	explicit HorizontalSlide(QWidget *parent);

	void setCurrentPage(QWidget *currentPage);
	QWidget *nextPage() const;
	void setNextPage(QWidget *nextPage);

public slots:
	void start(bool slideLeft, int speed);

private:
	QWidget *m_parentWidget;
	QWidget *m_currentPage;
	QWidget *m_nextPage;
	QLabel *m_labCurrent;
	QLabel *m_labNext;
	int m_width;
	int m_height;
	bool m_slideLeft;

private slots:
	void onValueChanged(const QVariant &value);
	void onAnimationFinished();

signals:
	void finished();
};

#endif // HORIZONTALSLIDE_H
