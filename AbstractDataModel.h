#ifndef ABSTRACTDATAMODEL_H
#define ABSTRACTDATAMODEL_H

#include "flatgui_global.h"
#include <QObject>

class AbstractDataModelPrivate;
class AbstractEditor;
class AbstractValidator;

class FLATGUISHARED_EXPORT AbstractDataModel : public QObject
{
	Q_OBJECT
public:
	explicit AbstractDataModel(QObject *parent = nullptr);
	~AbstractDataModel();

	virtual QVariant value() const = 0;
	virtual QString text() const = 0;
	virtual QVariant defaultValue() const = 0;
	virtual void setDefaultValue(const QVariant &value) = 0;
	virtual AbstractEditor *editor() const = 0;

	void setValidator(AbstractValidator *validator);

public slots:
	virtual void setValue(const QVariant &value) = 0;
	virtual void clear() = 0;

protected:
	AbstractValidator *validator() const;

private:
	AbstractDataModelPrivate *m_ptr;

private slots:
	virtual void onEditingFinished(bool accepted) = 0;

signals:
	void valueChanged();
};

#endif // ABSTRACTDATAMODEL_H
