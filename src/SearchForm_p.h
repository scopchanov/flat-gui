#ifndef SEARCHFORM_P_H
#define SEARCHFORM_P_H

class SearchForm;
class AbstractField;

class SearchFormPrivate
{
	explicit SearchFormPrivate(SearchForm *parent);

	AbstractField *field;
	int matchType;

	friend class SearchForm;
};

#endif // SEARCHFORM_P_H
