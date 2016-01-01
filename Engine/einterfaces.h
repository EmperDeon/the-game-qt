#ifndef G_MODINTERFACES
#define G_MODINTERFACES

#include <QString>
#include <QtWidgets>

#include "Engine/edefines.h"
#include "Engine/interfaces/imain.h"

#include "Engine/interfaces/iutils.h"
#include "Engine/interfaces/iinventory.h"
#include "Engine/interfaces/ilevel.h"
#include "Engine/interfaces/imods.h"
#include "Engine/interfaces/irender.h"
#include "Engine/interfaces/itext.h"



QT_BEGIN_NAMESPACE
// ModLoader
Q_DECLARE_INTERFACE(IModLoader, "org.ilzcorp.IModLoader")
//Q_DECLARE_INTERFACE(IModsIds, "org.ilzcorp.IModsIds")
//
//Q_DECLARE_INTERFACE(IItemsContainer, "org.ilzcorp.IItemsContainer")
//Q_DECLARE_INTERFACE(IItem, "org.ilzcorp.IItem")
//
//Q_DECLARE_INTERFACE(IBlocksContainer, "org.ilzcorp.IBlocksContainer")
//Q_DECLARE_INTERFACE(IBlock, "org.ilzcorp.IBlock")
//
////!ModLoader
////CoreMod
//
//Q_DECLARE_INTERFACE(ICoreMod, "org.ilzcorp.ICoreMod")
////Q_DECLARE_INTERFACE(IRender,  "org.ilzcorp.GRenderInterface")
//
////!CoreMod
////Mod
//
//Q_DECLARE_INTERFACE(IMod,     "org.ilzcorp.IMod")
//
////!Mod
////Engine
//
//Q_DECLARE_INTERFACE(IMain,    "org.ilzcorp.IMain")
//Q_DECLARE_INTERFACE(ILogger,  "org.ilzcorp.ILogger")
//Q_DECLARE_INTERFACE(IVars,    "org.ilzcorp.IVars")

//!Engine
// Q_DECLARE_INTERFACE(, "org.ilzcorp.")
QT_END_NAMESPACE
#endif