#include "ToolButton.h"
#include "ToolButton_p.h"
#include <QPaintEvent>
#include <QPainter>

/*!
 * \class ToolButton
 * \inmodule FlatGui
 */

ToolButton::ToolButton(QWidget *parent) :
	AbstractButton(parent),
	m_ptr(new ToolButtonPrivate)
{
	setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
}

ToolButton::~ToolButton()
{
	delete m_ptr;
}

void ToolButton::setPixmap(const QPixmap &pixmap)
{
	m_ptr->pixmap = pixmap;
	update();
}

/*!
 * \brief ToolButton::setSize
 */

void ToolButton::setSize(int n)
{
	m_ptr->pixmapOrigin.setX((n - m_ptr->pixmap.width())/2);
	m_ptr->pixmapOrigin.setY((n - m_ptr->pixmap.height())/2);
	m_ptr->scaleFactor = 1 - 5.0/n;

	resize(n, n);
	setFixedSize(n, n);
}

/*!
 * \brief Handles the painting of the ToolButton by drawing its content on a
 * canvas.
 *
 * When the button is pressed a visual confirmation for the user is created by
 * scaling the canvas and lowering its opacity. This event handler implements
 * the Template Method design pattern and depends on the subclasses to define
 * how the button will look like by letting them do the actual painting.
 *
 * \sa ToolButton::paint
 * \reimp
 */

void ToolButton::paintEvent(QPaintEvent *event)
{
	QPainter painter(this);
	bool clickable = isEnabled();

	painter.setClipping(true);
	painter.setClipRect(event->rect());
	painter.setRenderHint(QPainter::SmoothPixmapTransform);

	QPixmap canvas(size());
	QPainter canvasPainter;

	canvas.fill(Qt::transparent);

	canvasPainter.begin(&canvas);

	painter.setOpacity(clickable ? 1 : 0.25);

	paint(&canvasPainter);

	if (clickable && m_down) {
		painter.setOpacity(0.9);
		painter.translate(rect().center());
		painter.scale(m_ptr->scaleFactor, m_ptr->scaleFactor);
		painter.translate(-rect().center());
	}

	painter.drawPixmap(rect(), canvas);
}

/*!
 * \brief ToolButton::paint
 */

void ToolButton::paint(QPainter *painter)
{
	painter->drawPixmap(m_ptr->pixmapOrigin, m_ptr->pixmap);
}

void ToolButton::setPixmapOrigin(const QPoint &p)
{
	m_ptr->pixmapOrigin = p;
}

void ToolButton::setScaleFactor(qreal d)
{
	m_ptr->scaleFactor = d;
}

ToolButtonPrivate::ToolButtonPrivate() :
	scaleFactor(0.9)
{

}
