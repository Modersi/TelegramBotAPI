#ifndef TELEGRAMAPI_GLOBAL_H
#define TELEGRAMAPI_GLOBAL_H

#include <QtCore/qglobal.h>

/*! \mainpage My Personal Index Page

 */

#if defined(TELEGRAMAPI_LIBRARY)
#  define TELEGRAMAPI_EXPORT Q_DECL_EXPORT
#else
#  define TELEGRAMAPI_EXPORT Q_DECL_IMPORT
#endif

#endif // TELEGRAMAPI_GLOBAL_H
