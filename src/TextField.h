#ifndef TEXTFIELD_H
#define TEXTFIELD_H

#include "FancyField.h"

class FLATGUISHARED_EXPORT TextField : public FancyField
{
	Q_OBJECT
public:
	explicit TextField(QWidget *parent = nullptr);

	void setText(const QString &text);
	void setPlaceholderText(const QString &text) override;
	void setDefaultText(const QString &text);
};

#endif // TEXTFIELD_H
