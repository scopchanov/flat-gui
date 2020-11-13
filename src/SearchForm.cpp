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

#include "SearchForm.h"
#include "SearchForm_p.h"
#include "ToolButton.h"
#include "AbstractField.h"
#include "StaticDecoration.h"
#include "TextDataModel.h"
#include "PixmapBuilder.h"
#include <QHBoxLayout>
#include <QVariant>

/*!
 * \class SearchForm
 * \inmodule FlatGui
 */

SearchForm::SearchForm(QWidget *parent) :
	QWidget(parent),
	m_ptr(new SearchFormPrivate(this))
{
	const QString &placeholderText(tr("Enter search term"));
	auto *layoutMain = new QHBoxLayout(this);
	auto *model = new TextDataModel;
	auto *decoration = new StaticDecoration;
	auto *btnMatch = new ToolButton(this);

	model->setPlaceholderText(placeholderText);

	decoration->setPixmap(
				PixmapBuilder::create(PixmapBuilder::Glass,
									  palette().color(QPalette::Text)));

	m_ptr->field->setDataModel(model);
	m_ptr->field->setDecoration(decoration);
	m_ptr->field->setPlaceholderText(placeholderText);

	btnMatch->setPixmap(QPixmap(":/pix/images/icons/16/match-begins.png"));
	btnMatch->setSize(32);

	layoutMain->addWidget(btnMatch);
	layoutMain->addWidget(m_ptr->field);
	layoutMain->setContentsMargins(0, 0, 0, 0);
	layoutMain->setSpacing(0);

	setMinimumSize(150, 48);
	setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);

	connect(btnMatch, &ToolButton::clicked, this, &SearchForm::onMatchClicked);
	connect(m_ptr->field, &AbstractField::contentChanged,
			this, &SearchForm::contentChanged);
}

SearchForm::~SearchForm()
{
	delete m_ptr;
}

QString SearchForm::searchTerm() const
{
	return m_ptr->field->value().toString();
}

int SearchForm::matchType() const
{
	return m_ptr->matchType;
}

void SearchForm::onMatchClicked()
{
	auto *btnMatch = static_cast<ToolButton *>(sender());
	QString str(":/pix/images/icons/16/match-");

	m_ptr->matchType++;

	if (m_ptr->matchType > 3)
		m_ptr->matchType = 0;

	switch (m_ptr->matchType) {
	case 0:
		str.append("begins.png");
		break;
	case 1:
		str.append("contains.png");
		break;
	case 2:
		str.append("ends.png");
		break;
	case 3:
		str.append("exact.png");
		break;
	}

	btnMatch->setPixmap(str);

	contentChanged();
}

SearchFormPrivate::SearchFormPrivate(SearchForm *parent) :
	field(new AbstractField(parent)),
	matchType(0)
{

}
