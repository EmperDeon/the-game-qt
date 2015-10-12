#ifndef GLOBALQT_IINVENTORY_H
#define GLOBALQT_IINVENTORY_H

class Emiks;
class QString;
class IWorldBlock;

enum class GItemAction{
	Drop, Craft, Pickup
};
enum class GToolAction{
	Drop, Craft, Pickup,
	leftClick, shiftLeftClick, longLeftCLick, longShiftLeftClick,
	rightClick, shiftRightClick, longRightClick, longShiftRightClick
};
enum class GBlockAction{

};

class IModsIds {
public:
	virtual Emiks* get(QString m, QString i, QString k, int s) = 0;
};

class IItem{
public:
	virtual float getStackSize() = 0;
	virtual int getStackType() = 0;
};
class IItemsContainer{
public:
	virtual IItem* get(Emiks* id) = 0;
	virtual Emiks* get(IItem* it) = 0;
};

class ITool{
public:
	virtual QString getType() = 0;
	virtual int getDurability() = 0;
};
class IToolsContainer{
public:
	virtual ITool* get(Emiks* id) = 0;
	virtual Emiks* get(ITool* id) = 0;
};

class IItemStack{
public:
	virtual Emiks* getId() = 0;
};
class IToolStack : public IItemStack{

};

// Actions

class IActions{
public:
	virtual void item(GItemAction a, IItemStack* s) = 0;
	virtual void tool(GToolAction a, IToolStack* s) = 0;
	virtual void block(GBlockAction a, IWorldBlock * s) = 0;
};

class IItemActions{
public:
	virtual void event(GItemAction a, IItemStack* s)const = 0;
	virtual bool hasAction(GItemAction a)const = 0;
};
class IToolActions{
public:
	virtual void event(GToolAction a, IToolStack* s)const = 0;
	virtual bool hasAction(GItemAction a)const = 0;
};
class IBlockActions{
public:
	virtual void event(GBlockAction a, IWorldBlock* s)const = 0;
	virtual bool hasAction(GItemAction a)const = 0;
};
class IPluginActions{
public:
	virtual void item(GItemAction a, IItemStack* s)const = 0;
	virtual void tool(GToolAction a, IToolStack* s)const = 0;
	virtual void block(GBlockAction a, IWorldBlock * s) const = 0;
};
#endif //GLOBALQT_IINVENTORY_H
