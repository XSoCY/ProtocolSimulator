﻿#ifndef COMMUNICATIONCHANNELS_GLOBAL_H
#define COMMUNICATIONCHANNELS_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(COMMUNICATIONCHANNELS_LIBRARY)
#  define COMMUNICATIONCHANNELSSHARED_EXPORT Q_DECL_EXPORT
#else
#  define COMMUNICATIONCHANNELSSHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // COMMUNICATIONCHANNELS_GLOBAL_H