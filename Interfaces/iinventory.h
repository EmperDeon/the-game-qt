#ifndef GLOBALQT_IINVENTORY_H
#define GLOBALQT_IINVENTORY_H

class Imiks;
class QString;
class IWorldBlock;

// Enums
enum class IItemAction {
	Drop, Craft, Pickup
};

enum class IToolAction {
	Drop, Craft, Pickup,
	leftClick, shiftLeftClick, longLeftCLick, longShiftLeftClick,
	rightClick, shiftRightClick, longRightClick, longShiftRightClick
};

enum class IBlockAction {

};
// Enums


// Stacks
class IItemStack{
public:
	virtual Imiks getId() = 0;
};

class IToolStack : public IItemStack{

};
// Stacks

#endif //GLOBALQT_IINVENTORY_H
