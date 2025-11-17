#ifndef PAGECAPTURE_H
#define PAGECAPTURE_H

class QWidget;
class QPixmap;

class PageCapture
{
public:
	static QPixmap createSnapshot(QWidget *page);
};

#endif // PAGECAPTURE_H
