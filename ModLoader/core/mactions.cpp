#include "ModLoader/core/mactions.h"

MActions::MActions(MCoreMods *l):loader(l) {}

void MActions::item(GItemAction a, IItemStack *s) {
 if(itemScripts->contains(s->getId())){
	 itemScripts->value(s->getId())->event(a, s);
 }else if (plugins->contains(s->getId()->m())){
		plugins->value(s->getId()->m())->item(a, s);
 }
}

void MActions::tool(GToolAction a, IToolStack *s) {
	if(toolScripts->contains(s->getId())){
		toolScripts->value(s->getId())->event(a, s);
	}else if (plugins->contains(s->getId()->m())){
		plugins->value(s->getId()->m())->tool(a, s);
	}
}

void MActions::block(GBlockAction a, IWorldBlock *s) {
	if(blockScripts->contains(s->getId())){
		blockScripts->value(s->getId())->event(a, s);
	}else if (plugins->contains(s->getId()->m())){
		plugins->value(s->getId()->m())->block(a, s);
	}
}

void MItemActions::event(GItemAction a, IItemStack *s)const {}
bool MItemActions::hasAction(GItemAction a)const {	return false;}

void MToolActions::event(GToolAction a, IToolStack *s)const {}
bool MToolActions::hasAction(GItemAction a)const {	return false;}

void MBlockActions::event(GBlockAction a, IWorldBlock *s)const {}
bool MBlockActions::hasAction(GItemAction a)const { return false;}

void MPluginActions::item(GItemAction a, IItemStack *s) const {}
void MPluginActions::tool(GToolAction a, IToolStack *s) const {}
void MPluginActions::block(GBlockAction a, IWorldBlock *s) const {}
