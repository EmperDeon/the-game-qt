#ifndef GLOBALQT_MACTIONS_H
#define GLOBALQT_MACTIONS_H
#include <ModLoader/mdefines.h>
#include <ModLoader/core/mcoremods.h>


class MActions : public IActions{
	QMap <Imiks, IItemActions*>* itemScripts;
	QMap <Imiks, IToolActions*>* toolScripts;
	QMap <Imiks, IBlockActions*>* blockScripts;

	QMap <int, IPluginActions*>* plugins;
	
public:
	MActions();
	void item(GItemAction a, IItemStack* s)     override;
	void tool(GToolAction a, IToolStack* s)     override;
	void block(GBlockAction a, IWorldBlock * s) override;
};

class MItemActions : public IItemActions{
public:
	virtual void event(GItemAction a, IItemStack *s) const override;
	virtual bool hasAction(GItemAction a)            const override;
};

class MToolActions : public IToolActions{
public:
	virtual bool hasAction(GItemAction a)            const override;
	virtual void event(GToolAction a, IToolStack *s) const override;
};

class MBlockActions : public IBlockActions{
public:
	virtual bool hasAction(GItemAction a)              const override;
	virtual void event(GBlockAction a, IWorldBlock *s) const override;
};

class MPluginActions : public IPluginActions{
public:
	virtual void item(GItemAction a, IItemStack* s)     const override;
	virtual void tool(GToolAction a, IToolStack* s)     const override;
	virtual void block(GBlockAction a, IWorldBlock * s) const override;
};


#endif //GLOBALQT_MACTIONS_H
