#ifndef GLOBALQT_EMODINTERFACES_H
#define GLOBALQT_EMODINTERFACES_H

#include <Engine/edefines.h>
#include <Engine/interfaces/imain.h>

#include <Engine/interfaces/iutils.h>
#include <Engine/interfaces/iinventory.h>
#include <Engine/interfaces/iplayer.h>
#include <Engine/interfaces/irender.h>
#include <Engine/interfaces/ilevel.h>
#include <Engine/interfaces/imods.h>
#include <Engine/interfaces/itext.h>

QT_BEGIN_NAMESPACE
// Only for plugins
Q_DECLARE_INTERFACE(IModLoader, "org.ilzcorp.IModLoader")

QT_END_NAMESPACE


#endif //GLOBALQT_EMODINTERFACES_H