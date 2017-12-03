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

	decoration->setPixmap(PixmapBuilder::create(PixmapBuilder::Glass, palette().color(QPalette::Text)));

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
	connect(m_ptr->field, &AbstractField::contentChanged, this, &SearchForm::contentChanged);
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
