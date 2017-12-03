#ifndef TEXTEDITOR_H
#define TEXTEDITOR_H

#include "AbstractEditor.h"

class LineEdit;

class TextEditor : public AbstractEditor
{
	Q_OBJECT
public:
	explicit TextEditor(QWidget *parent = nullptr);

	QString text() const;
	void setText(const QString &str);
	void setPlaceholderText(const QString &str);

public slots:
	void reposition() override;

private:
	void setup() override;

	LineEdit *m_lineEdit;

private slots:
	void onEditingFinished();
};

#endif // TEXTEDITOR_H
