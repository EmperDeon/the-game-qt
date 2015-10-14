#ifndef GLOBALQT_MACTIONS_H
#define GLOBALQT_MACTIONS_H

#include <ModLoader/mdefines.h>
#include <ModLoader/core/mcoremods.h>
#include "Engine/einterfaces.h"

class MCoreMods;

class MActions : public IActions{
 Q_INTERFACES(IActions)
	MCoreMods* loader;

	QMap <Imiks, IItemActions*>* itemScripts;
	QMap <Imiks, IToolActions*>* toolScripts;
	QMap <Imiks, IBlockActions*>* blockScripts;

	QMap <int, IPluginActions*>* plugins;
public:
	MActions(MCoreMods* l);
	void item(GItemAction a, IItemStack* s) Q_DECL_OVERRIDE ;
	void tool(GToolAction a, IToolStack* s) Q_DECL_OVERRIDE ;
	void block(GBlockAction a, IWorldBlock * s) Q_DECL_OVERRIDE ;
};

class MItemActions : public IItemActions{
public:
	virtual void event(GItemAction a, IItemStack *s)const;
	virtual bool hasAction(GItemAction a)const;
};

class MToolActions : public IToolActions{
public:
	virtual bool hasAction(GItemAction a)const;
	virtual void event(GToolAction a, IToolStack *s)const;
};

class MBlockActions : public IBlockActions{
public:
	virtual bool hasAction(GItemAction a)const;
	virtual void event(GBlockAction a, IWorldBlock *s)const;
};

class MPluginActions : public IPluginActions{
public:
	virtual void item(GItemAction a, IItemStack* s)const;
	virtual void tool(GToolAction a, IToolStack* s)const;
	virtual void block(GBlockAction a, IWorldBlock * s) const;
};
#endif //GLOBALQT_MACTIONS_H
