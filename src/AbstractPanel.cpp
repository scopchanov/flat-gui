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

#include "AbstractPanel.h"
#include <QBoxLayout>

/*!
 * \class AbstractPanel
 * \inmodule FlatGui
 * \brief Base class for all panels.
 */

AbstractPanel::AbstractPanel(QWidget *parent) :
	QWidget(parent)
{
	setFocusPolicy(Qt::StrongFocus);
}

void AbstractPanel::addWidget(QWidget *widget)
{
	if (!widget)
		return;

	widget->setParent(this);
	layout()->addWidget(widget);

	fitTo(widget);
}

void AbstractPanel::addStretch()
{
	static_cast<QBoxLayout *>(layout())->addStretch();
}

void AbstractPanel::addSpacing(int n)
{
	static_cast<QBoxLayout *>(layout())->addSpacing(n);
}

void AbstractPanel::fitTo(QWidget *)
{

}
