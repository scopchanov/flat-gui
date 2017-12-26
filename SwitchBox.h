#ifndef SWITCHBOX_H
#define SWITCHBOX_H

#include "AbstractButton.h"

class SwitchBoxPrivate;

class FLATGUISHARED_EXPORT SwitchBox : public AbstractButton
{
	Q_OBJECT
public:
	explicit SwitchBox(QWidget *parent = nullptr);
	~SwitchBox();

	bool isChecked() const;
	void setChecked(bool checked);

protected:
	void paintEvent(QPaintEvent *event) override final;
	void doClick();

private:
	SwitchBoxPrivate *m_ptr;

private slots:
	void onValueChanged(const QVariant &value);
	void onFinished();
};

#endif // SWITCHBOX_H
