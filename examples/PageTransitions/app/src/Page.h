#ifndef PAGE_H
#define PAGE_H

#include <QWidget>

class QLabel;

class Page : public QWidget
{
	Q_OBJECT
public:
	explicit Page(QWidget *parent = nullptr);

	QString text() const;
	void setText(const QString &text);
	QPixmap image() const;
	void setImage(const QPixmap &image);

private:
	QLabel *_labelText;
	QLabel *_labelImage;
};

#endif // PAGE_H
