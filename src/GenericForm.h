#ifndef GENERICFORM_H
#define GENERICFORM_H

#include "flatgui_global.h"
#include <QWidget>

class GenericFormPrivate;
class AbstractField;

class FLATGUISHARED_EXPORT GenericForm : public QWidget
{
	Q_OBJECT
public:
	explicit GenericForm(QWidget *parent = nullptr);
	~GenericForm();

	void addField(AbstractField *field);

	bool isEmpty() const;
	bool isValid() const;
	QJsonObject content() const;

public slots:
	void clear() const;

private:
	GenericFormPrivate *m_ptr;

signals:
	void contentChanged();
};

#endif // GENERICFORM_H
