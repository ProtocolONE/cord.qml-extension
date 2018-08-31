#pragma once

#include <QtCore/qglobal.h>

#ifdef QMLEXTENSION_LIB
# define QMLEXTENSION_EXPORT Q_DECL_EXPORT
#else
# define QMLEXTENSION_EXPORT Q_DECL_IMPORT
#endif
