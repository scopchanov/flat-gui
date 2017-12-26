#ifndef LINEEDIT_H
#define LINEEDIT_H

#include <QLineEdit>

class LineEdit : public QLineEdit
{
	Q_OBJECT
public:
	explicit LineEdit(QWidget *parent = nullptr);

	bool isRejected() const;

protected:
	void keyPressEvent(QKeyEvent *event) override;

private:
	bool m_rejected;
};

#endif // LINEEDIT_H
