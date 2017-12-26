#ifndef ABSTRACTEDITOR_H
#define ABSTRACTEDITOR_H

#include "flatgui_global.h"
#include <QWidget>

class AbstractEditorPrivate;
class AbstractField;

class FLATGUISHARED_EXPORT AbstractEditor : public QWidget
{
	Q_OBJECT
public:
	explicit AbstractEditor(QWidget *parent = nullptr, Qt::WindowFlags f = Qt::WindowFlags());
	~AbstractEditor();

	AbstractField *field() const;
	void setField(AbstractField *field);

public slots:
	virtual void reposition() = 0;

protected:
	void showEvent(QShowEvent *) override;

private:
	virtual void setup();

	AbstractEditorPrivate *m_ptr;

signals:
	void editingFinished(bool accepted);
};

#endif // ABSTRACTEDITOR_H
