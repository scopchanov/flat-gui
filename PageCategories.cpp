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

ButtonCategory *PageCategories::createButton(const QString &name, const QString &description, const QPixmap &pixmap, QAction *act)
{
    return m_grid->createButton(name, description, pixmap, act);
}
