#ifndef TOOLBAR_H
#define TOOLBAR_H

#include "AbstractPanel.h"

class FLATGUISHARED_EXPORT ToolBar : public AbstractPanel
{
	Q_OBJECT
public:
	explicit ToolBar(QWidget *parent = nullptr);
};

#endif // TOOLBAR_H
