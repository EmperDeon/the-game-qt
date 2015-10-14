#ifndef GLOBALQT_IINVENTORY_H
#define GLOBALQT_IINVENTORY_H
#include <Engine/einterfaces.h>

class Imiks;
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


class IItemStack{
public:
	virtual Imiks getId() = 0;
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
