/**
MIT License

Copyright (c) 2020 Michael Scopchanov

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
