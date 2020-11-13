/**
MIT License

Copyright (c) 2018 Michael Scopchanov

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#include "AbstractField.h"
#include "AbstractField_p.h"
#include "AbstractDecoration.h"
#include "AbstractDataModel.h"
#include "AbstractEditor.h"
#include "ToolButton.h"
#include "PixmapBuilder.h"
#include <QPaintEvent>
#include <QPainter>
#include <QVariantAnimation>

/*!
 * \class AbstractField
 * \inmodule FlatGui
 */

/*!
 * \fn void AbstractField::contentChanged()
 * This signal is emitted when the content of the field
 * has changed.
 *
 * \since 1.0.0
 */

AbstractField::AbstractField(QWidget *parent) :
	AbstractButton(parent),
	m_ptr(new AbstractFieldPrivate)
{
	setFixedHeight(36);
	setAttribute(Qt::WA_TranslucentBackground);
}

AbstractField::~AbstractField()
{
	delete m_ptr;
}

/*!
 * Sets \a decoration as a decoration for this field.
 *
 * Field takes the ownership of \a decoration.
 *
 * The decoration provides an icon to be drawn in front
 * of the text. The icon may change depending on the
 * state of the field.
 *
 * If a nullptr is passed as argument this function
 * does nothing.
 *
 * \since 1.0.0
 */

void AbstractField::setDecoration(AbstractDecoration *decoration)
{
	if (!decoration)
		return;

	decoration->setParent(this);
	m_ptr->decoration = decoration;
}

AbstractDataModel *AbstractField::dataModel() const
{
	return m_ptr->model;
}

/*!
 * Sets \a model as a data model for this field.
 *
 * Field takes the ownership of \a model.
 *
 * If a nullptr is passed as argument this function
 * does nothing.
 *
 * \since 1.0.0
 */

void AbstractField::setDataModel(AbstractDataModel *model)
{
	if (!model)
		return;

	model->setParent(this);
	m_ptr->model = model;
	m_ptr->text = m_ptr->model->text();

	connect(model, &AbstractDataModel::valueChanged, this, &AbstractField::onValueChanged);
}

/*!
 * \property AbstractField::required
 * \brief whether the field must be filled by the user.
 *
 * This property affects the result of isValid.
 *
 * By default, this property is \c false.
 *
 * \since 1.0.0
 *
 * \sa isValid
 */

bool AbstractField::isRequired() const
{
	return m_ptr->required;
}

void AbstractField::setRequired(bool b)
{
	m_ptr->required = b;
	contentChanged();
}

/*!
 * \property AbstractField::placeholderText
 * \brief The text which should be displayed if the
 * field is empty.
 *
 * By default, this property holds an empty string.
 *
 * \since 1.0.0
 *
 * \sa isEmpty
 */

QString AbstractField::placeholderText() const
{
	return m_ptr->placeholderText;
}

void AbstractField::setPlaceholderText(const QString &text)
{
	m_ptr->placeholderText = text;
}

QVariant AbstractField::value() const
{
	if (!m_ptr->model)
		return QVariant();

	return m_ptr->model->value();
}

/*!
 * Returns \c true if the field contains no text;
 * otherwise returns \c false.
 *
 * \since 1.0.0
 */

bool AbstractField::isEmpty() const
{
	return m_ptr->text.isEmpty();
}

/*!
 * Returns \c false if the field is marked as required
 * but contains no text; otherwise returns \c true.
 *
 * \since 1.0.0
 */

bool AbstractField::isValid() const
{
	return !(m_ptr->required && m_ptr->text.isEmpty());
}

QRect AbstractField::textArea() const
{
	return rect().adjusted(m_ptr->decoration ? 32 : 10, 2, m_ptr->btnClear ? -34 : -2, -2);
}

void AbstractField::clear()
{
	m_ptr->model->clear();
}

void AbstractField::activate()
{
	m_ptr->active = true;
	repaint();
}

void AbstractField::deactivate()
{
	m_ptr->active = false;
	repaint();
}

void AbstractField::paintEvent(QPaintEvent *event)
{
	QPainter painter(this);
	int leftMargin = 12;
	bool hasText = !m_ptr->text.isEmpty();

	painter.setClipping(true);
	painter.setClipRect(event->rect());

	painter.fillRect(rect().adjusted(1, 1, -2, -2), palette().color(QPalette::Button));

	if (m_ptr->decoration) {
		m_ptr->decoration->paint(&painter);
		leftMargin = 34;
	}

	const QRect &textRect(rect().adjusted(leftMargin, 0, m_ptr->btnClear ? -37 : -5, -1));
	const QString &elidedText(fontMetrics().elidedText(hasText ? m_ptr->text : m_ptr->placeholderText, Qt::ElideRight, textRect.width()));

	painter.setPen(palette().color(hasText ? QPalette::WindowText : QPalette::Mid));
	painter.drawText(textRect, Qt::TextSingleLine | Qt::AlignLeft | Qt::AlignVCenter, elidedText);

	painter.setPen(palette().color(QPalette::Dark));

	if (m_down || m_ptr->active) {
		painter.setPen(palette().color(QPalette::Highlight));
		painter.drawRect(rect().adjusted(0, 0, -1, -1));
	}

	painter.drawRect(rect().adjusted(1, 1, -2, -2));
}

void AbstractField::resizeEvent(QResizeEvent *)
{
	if (!m_ptr->btnClear)
		return;

	m_ptr->btnClear->move(width() - 34, 2);
}

void AbstractField::doClick()
{
	if (!m_ptr->model)
		return;

	AbstractEditor *editor = m_ptr->model->editor();

	if (!editor)
		return;

	activate();

	editor->setField(this);
	editor->reposition();
	editor->show();
	editor->setFocus();

	connect(editor, &AbstractEditor::destroyed, this, &AbstractField::deactivate);
}

void AbstractField::onValueChanged()
{
	m_ptr->text = m_ptr->model->text();

	update();
	contentChanged();

	if (m_ptr->text.isEmpty() && m_ptr->btnClear) {
		m_ptr->btnClear->deleteLater();	// Deleting the button immediately using 'delete' causes a crash
		update();
		return;
	}

	if (m_ptr->btnClear)
		return;

	m_ptr->btnClear = new ToolButton(this);
	m_ptr->btnClear->setPixmap(PixmapBuilder::create(PixmapBuilder::Cross, palette().color(QPalette::Text)));
	m_ptr->btnClear->setBackgroundRole(QPalette::Window);
	m_ptr->btnClear->setAutoFillBackground(true);
	m_ptr->btnClear->setSize(32);
	m_ptr->btnClear->move(width() - 34, 2);
	m_ptr->btnClear->show();

	connect(m_ptr->btnClear, &ToolButton::clicked, this, &AbstractField::clear);
	connect(m_ptr->btnClear, &ToolButton::destroyed, this, &AbstractField::onButtonClearDestroyed);
}

void AbstractField::onButtonClearDestroyed()
{
	m_ptr->btnClear = nullptr;
}

AbstractFieldPrivate::AbstractFieldPrivate() :
	model(nullptr),
	decoration(nullptr),
	btnClear(nullptr),
	required(false),
	active(false)
{

}
