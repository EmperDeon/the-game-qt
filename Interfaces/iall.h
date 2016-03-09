#ifndef GLOBALQT_IALL_H
#define GLOBALQT_IALL_H

#include <QtCore/qobject.h>

enum class ILogLevel {ERR = 1, WARN = 2, INFO = 3, DEBUG = 4, FINE = 5, FFINE = 6, ALL = 7, QT = 8};

#include <imain.h>
#include <iutils.h>
#include <ievent.h>
#include <iinventory.h>
#include <iplayer.h>
#include <irender.h>
#include <ilevel.h>
#include <imods.h>
#include <itext.h>

QT_BEGIN_NAMESPACE
	Q_DECLARE_INTERFACE(IModLoader, "org.ilzcorp.IModLoader")
 Q_DECLARE_INTERFACE(ICoreMod, "org.ilzcorp.ICoreMod")
 Q_DECLARE_INTERFACE(IMod, "org.ilzcorp.IMod")
QT_END_NAMESPACE

#endif //GLOBALQT_IALL_H
