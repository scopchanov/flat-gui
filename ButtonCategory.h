#ifndef BUTTONCATEGORY_H
#define BUTTONCATEGORY_H

#include "ToolButton.h"

class ButtonCategoryPrivate;

class ButtonCategory : public ToolButton
{
	Q_OBJECT
public:
	explicit ButtonCategory(QWidget *parent = nullptr);
	~ButtonCategory();

	void setName(const QString &str);
	void setDescription(const QString &str);
	void setSize(int n);

protected:
	void paint(QPainter *painter) override;

private:
	ButtonCategoryPrivate *m_ptr;
};

#endif // BUTTONCATEGORY_H
