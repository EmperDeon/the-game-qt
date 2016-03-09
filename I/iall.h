#ifndef GLOBALQT_IALL_H
#define GLOBALQT_IALL_H

#include <QtCore/qobject.h>

enum class ILogLevel {ERR = 1, WARN = 2, INFO = 3, DEBUG = 4, FINE = 5, FFINE = 6, ALL = 7, QT = 8};

#include <interf/imain.h>
#include <interf/iutils.h>
#include <interf/ievent.h>
#include <interf/iinventory.h>
#include <interf/iplayer.h>
#include <interf/irender.h>
#include <interf/ilevel.h>
#include <interf/imods.h>
#include <interf/itext.h>

QT_BEGIN_NAMESPACE
	Q_DECLARE_INTERFACE(IModLoader, "org.ilzcorp.IModLoader")
 Q_DECLARE_INTERFACE(ICoreMod, "org.ilzcorp.ICoreMod")
 Q_DECLARE_INTERFACE(IMod, "org.ilzcorp.IMod")
QT_END_NAMESPACE

#endif //GLOBALQT_IALL_H
