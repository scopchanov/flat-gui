#ifndef ABSTRACTBUTTON_H
#define ABSTRACTBUTTON_H

#include "flatgui_global.h"
#include <QWidget>

class FLATGUISHARED_EXPORT AbstractButton : public QWidget
{
    Q_OBJECT
public:
    explicit AbstractButton(QWidget *parent);

    bool event(QEvent *event) override;

protected:
    void actionEvent(QActionEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;

    virtual QRect clickArea() const;
    virtual void doClick();
    void setDown(bool down);

    bool m_pressed;
    bool m_down;

signals:
    void clicked();
};

#endif // ABSTRACTBUTTON_H
