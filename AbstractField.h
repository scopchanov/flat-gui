#ifndef ABSTRACTFIELD_H
#define ABSTRACTFIELD_H

#include "AbstractButton.h"

class AbstractFieldPrivate;
class AbstractDecoration;
class AbstractDataModel;

class FLATGUISHARED_EXPORT AbstractField : public AbstractButton
{
	Q_OBJECT
	Q_PROPERTY(QString placeholderText READ placeholderText WRITE setPlaceholderText)
	Q_PROPERTY(bool required READ isRequired WRITE setRequired)
public:
	explicit AbstractField(QWidget *parent = nullptr);
	~AbstractField();

	void setDecoration(AbstractDecoration *decoration);
	AbstractDataModel *dataModel() const;
	void setDataModel(AbstractDataModel *model);
	bool isRequired() const;
	void setRequired(bool b);
	QString placeholderText() const;
	virtual void setPlaceholderText(const QString &text);

	QVariant value() const;
	bool isEmpty() const;
	bool isValid() const;
	QRect textArea() const;

public slots:
	void clear();
	void activate();
	void deactivate();

protected:
	void paintEvent(QPaintEvent *event) override;
	void resizeEvent(QResizeEvent *) override;
	void doClick() override;

private:
	AbstractFieldPrivate *m_ptr;

private slots:
	void onValueChanged();
	void onButtonClearDestroyed();

signals:
	void contentChanged();
};

#endif // ABSTRACTFIELD_H
