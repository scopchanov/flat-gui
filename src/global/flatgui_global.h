#ifndef FLATGUI_GLOBAL_H
#define FLATGUI_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(FLATGUI_LIBRARY)
#define FLATGUI_EXPORT Q_DECL_EXPORT
#else
#define FLATGUI_EXPORT Q_DECL_IMPORT
#endif

#endif // FLATGUI_GLOBAL_H
