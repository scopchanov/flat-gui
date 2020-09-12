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

#include "PageCategories.h"
#include "GridWidget.h"
#include <QVBoxLayout>
#include <QScrollArea>

/*!
 * \class PageCategories
 * \inmodule FlatGui
 */

PageCategories::PageCategories(QWidget *parent) :
    QWidget(parent),
    m_grid(new GridWidget())
{
    auto *layoutMain = new QVBoxLayout(this);
    auto *scrollArea = new QScrollArea(this);

    scrollArea->setFrameStyle(QFrame::NoFrame);
    scrollArea->setAlignment(Qt::AlignLeft | Qt::AlignTop);
    scrollArea->setWidgetResizable(true);
    scrollArea->setWidget(m_grid);
    scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    layoutMain->addWidget(scrollArea);
    layoutMain->setContentsMargins(0, 0, 0, 0);
}

void PageCategories::setDescription(const QString &text)
{
    m_grid->setDescription(text);
}

ButtonCategory *PageCategories::createButton(const QString &name,
											 const QString &description,
											 const QPixmap &pixmap,
											 QAction *act)
{
    return m_grid->createButton(name, description, pixmap, act);
}
