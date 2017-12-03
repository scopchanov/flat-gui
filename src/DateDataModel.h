#ifndef DATEDATAMODEL_H
#define DATEDATAMODEL_H

#include "AbstractDataModel.h"

class DateDataModelPrivate;

class FLATGUISHARED_EXPORT DateDataModel : public AbstractDataModel
{
	Q_OBJECT
public:
	explicit DateDataModel(QObject *parent = nullptr);
	~DateDataModel();

	QVariant value() const override;
	QString text() const override;
	QVariant defaultValue() const override;
	void setDefaultValue(const QVariant &value) override;
	AbstractEditor *editor() const override;

public slots:
	void setValue(const QVariant &value) override;
	void clear() override;

private:
	DateDataModelPrivate *m_ptr;

private slots:
	void onEditingFinished(bool accepted) override;
};

#endif // DATEDATAMODEL_H
