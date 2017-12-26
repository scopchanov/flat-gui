#ifndef PUSHBUTTON_H
#define PUSHBUTTON_H

#include "AbstractButton.h"

class PushButtonPrivate;

class FLATGUISHARED_EXPORT PushButton : public AbstractButton
{
	Q_OBJECT
public:
	explicit PushButton(QWidget *parent = nullptr);
	~PushButton();

	void setText(const QString &text);
	void setDefault(bool b);

protected:
	bool event(QEvent *event) override;
	void paintEvent(QPaintEvent *event) override;

private:
	void setSize();

	PushButtonPrivate *m_ptr;

private slots:
	void onHighlightChanged(const QVariant &value);
};

#endif // PUSHBUTTON_H
