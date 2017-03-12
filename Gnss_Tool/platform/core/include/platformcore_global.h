#ifndef PLATFORMLOGIC_GLOBAL_H
#define PLATFORMLOGIC_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(PLATFORM_CORE_LIBRARY)
#  define PLATFORM_CORE_DLLSPEC Q_DECL_EXPORT
#else
#  define PLATFORM_CORE_DLLSPEC Q_DECL_IMPORT
#endif

#endif // PLATFORMLOGIC_GLOBAL_H
