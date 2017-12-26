#include "SwitchBox.h"
#include "SwitchBox_p.h"
#include <QPaintEvent>
#include <QPainter>
#include <QVariantAnimation>

SwitchBox::SwitchBox(QWidget *parent) :
	AbstractButton(parent),
	m_ptr(new SwitchBoxPrivate(this))
{
	m_ptr->createPixmapSlider();

	resize(72, 36);
	setFixedSize(72, 36);
}

SwitchBox::~SwitchBox()
{
	delete m_ptr;
}

bool SwitchBox::isChecked() const
{
	return m_ptr->checked;
}

void SwitchBox::setChecked(bool checked)
{
	m_ptr->checked = checked;
	m_ptr->offset = checked ? 39 : 3;
	update();
}

void SwitchBox::paintEvent(QPaintEvent *event)
{
	QPainter painter(this);

	painter.setClipping(true);
	painter.setClipRect(event->rect());

	painter.fillRect(rect().adjusted(1, 2, -1, -2), palette().color(QPalette::Light));
	painter.fillRect(rect().adjusted(1, 2, m_ptr->offset - rect().width() - 1, -2), palette().color(QPalette::Highlight));

	painter.drawPixmap(m_ptr->offset, 3, 30, 30, m_ptr->pixmap);

	painter.setPen(palette().color(QPalette::Dark));

	if (m_down) {
		painter.setPen(palette().color(QPalette::Highlight));
		painter.drawRect(rect().adjusted(0, 0, -1, -1));
	}

	painter.drawRect(rect().adjusted(1, 1, -2, -2));
}

void SwitchBox::doClick()
{
	if (m_ptr->busy)
		return;

	auto *animation = new QVariantAnimation(this);

	m_ptr->busy = true;

	animation->setStartValue(m_ptr->offset);
	animation->setEndValue(m_ptr->checked ? 3 : 39);
	animation->setDuration(150);
	animation->start(QAbstractAnimation::DeleteWhenStopped);

	connect(animation, &QVariantAnimation::valueChanged, this, &SwitchBox::onValueChanged);
	connect(animation, &QVariantAnimation::finished, this, &SwitchBox::onFinished);
}

void SwitchBox::onValueChanged(const QVariant &value)
{
	m_ptr->offset = value.toInt();
	repaint();
}

void SwitchBox::onFinished()
{
	m_ptr->checked ^= true;
	m_ptr->busy = false;
	repaint();
	clicked();
}

SwitchBoxPrivate::SwitchBoxPrivate(SwitchBox *parent) :
	p_ptr(parent),
	offset(3),
	checked(false),
	busy(false),
	pixmap(QPixmap(30, 30))
{

}

void SwitchBoxPrivate::createPixmapSlider()
{
	QPainter painter;

	pixmap.fill(p_ptr->palette().color(QPalette::Button));

	painter.begin(&pixmap);
	painter.setPen(p_ptr->palette().color(QPalette::Mid));
	painter.drawRect(0, 0, 29, 29);
	painter.setPen(QPen(p_ptr->palette().color(QPalette::Midlight), 2));
	painter.drawLine(11, 11, 11, 19);
	painter.drawLine(15, 11, 15, 19);
	painter.drawLine(19, 11, 19, 19);
}
