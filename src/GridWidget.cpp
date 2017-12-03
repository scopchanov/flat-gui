#include "GridWidget.h"
#include "GridWidget_p.h"
#include "ButtonCategory.h"
#include <QVBoxLayout>
#include <QAction>
#include <QLabel>

GridWidget::GridWidget(QWidget *parent) :
	QWidget(parent),
	m_ptr(new GridWidgetPrivate(this))
{
	new QVBoxLayout(this);	// A dummy layout is necessary to force
							// the scroll area to update the scroll
							// bar when the widget is resized while
							// being hidden.
	QFont f(font());

	f.setPointSize(10);

	m_ptr->label->setFont(f);
	m_ptr->label->setWordWrap(true);
	m_ptr->label->setForegroundRole(QPalette::Text);

	setAutoFillBackground(true);
}

GridWidget::~GridWidget()
{
	delete m_ptr;
}

void GridWidget::setDescription(const QString &text)
{
	m_ptr->label->setText(text);
}

ButtonCategory *GridWidget::createButton(const QString &name, const QString &description, const QPixmap &pixmap, QAction *act)
{
	auto *button = new ButtonCategory(this);

	button->setName(name);
	button->setDescription(description);
	button->setPixmap(pixmap);
	button->addAction(act);

	m_ptr->buttons.append(button);

	return button;
}

void GridWidget::resizeEvent(QResizeEvent *)
{
	int cnt = m_ptr->buttons.count();
	int w = width();
	int buttonsInRow = w/m_ptr->buttonSize;
	int neededHorizontalSpace = m_ptr->fullSize*buttonsInRow + m_ptr->spacing;

	if (neededHorizontalSpace > w)
		buttonsInRow--;

	if (buttonsInRow > cnt)
		buttonsInRow = cnt;

	if (buttonsInRow == 0)
		buttonsInRow = 1;

	neededHorizontalSpace = m_ptr->fullSize*buttonsInRow - m_ptr->spacing;

	m_ptr->label->resize(neededHorizontalSpace, m_ptr->label->heightForWidth(neededHorizontalSpace));

	int numberOfRows = ceil(static_cast<qreal>(cnt) / buttonsInRow);
	int neededVerticalSpace = m_ptr->fullSize*numberOfRows - m_ptr->spacing;
	int topMargin = (height() - neededVerticalSpace)/2;
	int spacingTop = m_ptr->label->height() + 3*m_ptr->spacing;

	if (topMargin < spacingTop)
		topMargin = spacingTop;

	int m = 0;
	int n = 0;
	int leftMargin = (w - neededHorizontalSpace)/2;

	if (leftMargin < m_ptr->spacing)
		leftMargin = m_ptr->spacing;

	foreach (QWidget *button, m_ptr->buttons) {
		button->move(m_ptr->fullSize*n + leftMargin, m_ptr->fullSize*m + topMargin);
		n++;

		if ((m_ptr->buttons.indexOf(button) % buttonsInRow) == (buttonsInRow - 1)) {
			n = 0;
			m++;
		}
	}

	m_ptr->label->move(leftMargin, topMargin - m_ptr->label->height() - m_ptr->spacing);
	m_ptr->actualHeight = topMargin + neededVerticalSpace + m_ptr->spacing;
}

QSize GridWidget::minimumSizeHint() const
{
	return QSize(-1, m_ptr->actualHeight);
}

GridWidgetPrivate::GridWidgetPrivate(GridWidget *parent) :
	buttonSize(200),
	spacing(12),
	fullSize(buttonSize + spacing),
	actualHeight(0),
	label(new QLabel(parent))
{

}
