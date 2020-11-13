/**
MIT License

Copyright (c) 2018 Michael Scopchanov

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

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
