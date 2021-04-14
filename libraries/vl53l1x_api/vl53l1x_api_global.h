#ifndef VL53L1X_API_GLOBAL_H
#define VL53L1X_API_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(VL53L1X_API_LIBRARY)
#  define VL53L1X_API_EXPORT Q_DECL_EXPORT
#else
#  define VL53L1X_API_EXPORT Q_DECL_IMPORT
#endif

#endif // VL53L1X_API_GLOBAL_H
