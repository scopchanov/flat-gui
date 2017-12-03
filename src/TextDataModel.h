#ifndef TEXTDATAMODEL_H
#define TEXTDATAMODEL_H

#include "AbstractDataModel.h"

class TextDataModelPrivate;

class FLATGUISHARED_EXPORT TextDataModel : public AbstractDataModel
{
	Q_OBJECT
public:
	explicit TextDataModel(QObject *parent = nullptr);
	~TextDataModel();

	QVariant value() const override;
	QString text() const override;
	QVariant defaultValue() const override;
	void setDefaultValue(const QVariant &value) override;
	AbstractEditor *editor() const override;
	void setPlaceholderText(const QString &text);

public slots:
	void setValue(const QVariant &value) override;
	void clear() override;

private:
	TextDataModelPrivate *m_ptr;

private slots:
	void onEditingFinished(bool accepted) override;
};

#endif // TEXTDATAMODEL_H
