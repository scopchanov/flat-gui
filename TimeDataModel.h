#ifndef TIMEDATAMODEL_H
#define TIMEDATAMODEL_H

#include "AbstractDataModel.h"

class TimeDataModelPrivate;

class FLATGUISHARED_EXPORT TimeDataModel : public AbstractDataModel
{
	Q_OBJECT
public:
	explicit TimeDataModel(QObject *parent = nullptr);
	~TimeDataModel();

	QVariant value() const override;
	QString text() const override;
	QVariant defaultValue() const override;
	void setDefaultValue(const QVariant &value) override;
	AbstractEditor *editor() const override;

public slots:
	void setValue(const QVariant &value) override;
	void clear() override;

private:
	TimeDataModelPrivate *m_ptr;

private slots:
	void onEditingFinished(bool accepted) override;
};

#endif // TIMEDATAMODEL_H
