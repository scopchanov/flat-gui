#ifndef PAGECATEGORIES_H
#define PAGECATEGORIES_H

#include "flatgui_global.h"
#include <QWidget>

class GridWidget;
class ButtonCategory;

class FLATGUISHARED_EXPORT PageCategories : public QWidget
{
    Q_OBJECT
public:
    explicit PageCategories(QWidget *parent = nullptr);

    void setDescription(const QString &text);
    ButtonCategory *createButton(const QString &name, const QString &description, const QPixmap &pixmap, QAction *act);

private:
    GridWidget *m_grid;
};

#endif // PAGECATEGORIES_H
