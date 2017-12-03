#ifndef FANCYFIELD_H
#define FANCYFIELD_H

#include "AbstractField.h"

class DynamicDecoration;

class FancyField : public AbstractField
{
	Q_OBJECT
public:
	explicit FancyField(QWidget *parent = nullptr);

private:
	DynamicDecoration *m_decoration;

private slots:
	void onContentChanged();
};

#endif // FANCYFIELD_H
