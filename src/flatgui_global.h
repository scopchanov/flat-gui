#ifndef FLATGUI_GLOBAL_H
#define FLATGUI_GLOBAL_H

#include <QtCore/qglobal.h>

// #if defined(FLATGUI_LIBRARY)
// #  define FLATGUISHARED_EXPORT Q_DECL_EXPORT
// #else
// #  define FLATGUISHARED_EXPORT Q_DECL_IMPORT
// #endif

#if defined(FLATGUI_LIBRARY)
#  define FLATGUISHARED_EXPORT 
#else
#  define FLATGUISHARED_EXPORT 
#endif


#endif // FLATGUI_GLOBAL_H
