/**
MIT License

Copyright (c) 2020 Michael Scopchanov

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

#include "DateEditor.h"
#include "AbstractField.h"
#include "ToolBar.h"
#include "MonthView.h"
#include "PixmapBuilder.h"
#include "components/SToolButton.h"
#include <QLocale>
#include <QPalette>
#include <QKeyEvent>
#include <QVBoxLayout>
#include <QLabel>

/*!
 * \class DateEditor
 * \inmodule FlatGui
 * \brief
 */

DateEditor::DateEditor(QWidget *parent) :
	AbstractEditor(parent, Qt::FramelessWindowHint | Qt::Popup),
	m_view(new MonthView(this)),
	m_labTitle(new QLabel(m_view->title(), this))
{
	auto *layoutMain = new QVBoxLayout(this);
	auto *toolbar = new ToolBar(this);
	auto *labDays = new QLabel(this);
	auto *btnBack = new SToolButton(this);
	auto *btnNext = new SToolButton(this);

	btnBack->setPixmap(PixmapBuilder::create(PixmapBuilder::Back,
											 palette().color(QPalette::Text)));
	btnBack->setSize(48);

	btnNext->setPixmap(PixmapBuilder::create(PixmapBuilder::Next,
											 palette().color(QPalette::Text)));
	btnNext->setSize(48);

	toolbar->addWidget(btnBack);
	toolbar->addStretch();
	toolbar->addWidget(m_labTitle);
	toolbar->addStretch();
	toolbar->addWidget(btnNext);
	toolbar->setFixedHeight(48);

	QString str("<table cellspacing='0'><tr>");

	for (int n = 0; n < 7; n++)
		str.append("<td style='color: "
				   + palette().color(n < 5
									 ? QPalette::ButtonText
									 : QPalette::Mid).name()
				   + "' width='48' align='center'>"
				   + QString(QLocale().dayName(n + 1).toUpper().at(0))
				   + "</td>");

	str.append("</tr></table>");

	labDays->setText(str);
	labDays->setFixedHeight(48);

	layoutMain->addWidget(toolbar);
	layoutMain->addWidget(labDays);
	layoutMain->addWidget(m_view);
	layoutMain->setContentsMargins(1, 1, 1, 1);
	layoutMain->setSpacing(0);

	setAttribute(Qt::WA_DeleteOnClose);
	setAttribute(Qt::WA_StyledBackground);
	setFixedSize(336, 384);
	setStyleSheet(".DateEditor { border: 1px solid palette(mid); }");

	connect(btnBack, &SToolButton::clicked, m_view, &MonthView::onDecClicked);
	connect(btnNext, &SToolButton::clicked, m_view, &MonthView::onIncClicked);
	connect(m_view, &MonthView::monthChanged, m_labTitle, &QLabel::setText);
	connect(m_view, &MonthView::dateChanged, this, &DateEditor::onDateChanged);
}

QDate DateEditor::date() const
{
	return m_view->date();
}

void DateEditor::setDate(const QDate &date)
{
	if (!date.isValid())
		return;

	m_view->setDate(date);
	m_labTitle->setText(m_view->title());
}

void DateEditor::reposition()
{
	auto *field = this->field();

	if (!field)
		return;

	resize(field->width(), 300);
	move(field->mapToGlobal(field->rect().bottomLeft()) += QPoint(0, 3));
}

void DateEditor::onDateChanged(const QDate &)
{
	editingFinished(true);
}
