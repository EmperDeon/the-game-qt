#ifndef GLOBALQT_EINTERFACES_H
#define GLOBALQT_EINTERFACES_H

#include <Engine/edefines.h>
#include <Engine/interfaces/imain.h>

#include <Engine/interfaces/iutils.h>
#include <Engine/interfaces/ievent.h>
#include <Engine/interfaces/iinventory.h>
#include <Engine/interfaces/iplayer.h>
#include <Engine/interfaces/irender.h>
#include <Engine/interfaces/ilevel.h>
#include <Engine/interfaces/imods.h>
#include <Engine/interfaces/itext.h>

QT_BEGIN_NAMESPACE
// Only for plugins
Q_DECLARE_INTERFACE(IModLoader, "org.ilzcorp.IModLoader")
Q_DECLARE_INTERFACE(ICoreMod, "org.ilzcorp.ICoreMod")
Q_DECLARE_INTERFACE(IMod, "org.ilzcorp.IMod")

QT_END_NAMESPACE


#endif //GLOBALQT_EINTERFACES_H