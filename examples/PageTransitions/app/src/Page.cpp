#include "Page.h"
#include <QBoxLayout>
#include <QLabel>

Page::Page(QWidget *parent) :
	QWidget{parent},
	_labelText{new QLabel(this)},
	_labelImage{new QLabel(this)}

{
	auto *layoutMain{new QVBoxLayout(this)};

	_labelText->setWordWrap(true);
	_labelImage->setAlignment(Qt::AlignCenter);

	layoutMain->addWidget(_labelText);
	layoutMain->addSpacing(20);
	layoutMain->addWidget(_labelImage);
	layoutMain->addStretch();
	layoutMain->setContentsMargins(20, 20, 20, 20);
	layoutMain->setSpacing(0);

	setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Maximum);
}

QString Page::text() const
{
	return _labelText->text();
}

void Page::setText(const QString &text)
{
	_labelText->setText(text);
}

QPixmap Page::image() const
{
	return _labelImage->pixmap();
}

void Page::setImage(const QPixmap &image)
{
	_labelImage->setPixmap(image);
}
