#ifndef UTIL_SELF_GLOBAL_H
#define UTIL_SELF_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(UTIL_SELF_LIBRARY)
#  define UTILSHARED_SELF_EXPORT Q_DECL_EXPORT
#else
#  define UTILSHARED_SELF_EXPORT Q_DECL_IMPORT
#endif

#endif // UTIL_GLOBAL_H
