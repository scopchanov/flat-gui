#include "PageCapture.h"
#include <QWidget>

QPixmap PageCapture::createSnapshot(QWidget *page)
{
	if (!page || !page->size().isValid())
		return {};

	QSize pageSize{page->size()};
	qreal devicePixelRatio{page->devicePixelRatioF()};
	QPixmap pixmap(pageSize * devicePixelRatio);

	pixmap.setDevicePixelRatio(devicePixelRatio);

	page->render(&pixmap);

	return pixmap;
}
