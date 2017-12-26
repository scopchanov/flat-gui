#include "FancyField.h"
#include "DynamicDecoration.h"
#include "PixmapBuilder.h"

FancyField::FancyField(QWidget *parent) :
	AbstractField(parent),
	m_decoration(new DynamicDecoration)
{
	m_decoration->setPixmapOn(PixmapBuilder::create(PixmapBuilder::Grid, palette().color(QPalette::Highlight)));
	m_decoration->setPixmapOff(PixmapBuilder::create(PixmapBuilder::Grid, palette().color(QPalette::Light)));

	setDecoration(m_decoration);

	connect(this, &FancyField::contentChanged, this, &FancyField::onContentChanged);
}

void FancyField::onContentChanged()
{
	m_decoration->setState(!isValid());
}
