#ifndef PLATFROMLOGIC_GLOBAL_H
#define PLATFROMLOGIC_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(COREPLATFORM_LIBRARY)
#  define PLATFORMLOGIC_EXPORT Q_DECL_EXPORT
#else
#  define PLATFORMLOGIC_EXPORT Q_DECL_IMPORT
#endif

#endif // PLATFROMLOGIC_GLOBAL_H
