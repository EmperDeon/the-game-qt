#ifndef GLOBALQT_MACTIONS_H
#define GLOBALQT_MACTIONS_H

#include <ModLoader/mdefines.h>
#include <ModLoader/mods/mmods.h>
#include "Engine/einterfaces.h"

class MMods;

class MActions : public IActions{
 Q_INTERFACES(IActions)
	MMods* loader;

public:
	MActions(MMods* l);
	void item(GItemAction a, IItemStack* s) Q_DECL_OVERRIDE ;
	void tool(GToolAction a, IToolStack* s) Q_DECL_OVERRIDE ;
	void block(GBlockAction a, IWorldBlock * s) Q_DECL_OVERRIDE ;
};

#endif //GLOBALQT_MACTIONS_H
