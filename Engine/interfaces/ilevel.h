#ifndef GLOBALQT_ILEVEL_H
#define GLOBALQT_ILEVEL_H
class Emiks;

class IBlock{
public:
	virtual float getWeight() = 0;
};

class IBlocksContainer{
public:
	virtual IBlock* get(Emiks* id) = 0;
	virtual Emiks* get(IBlock* id) = 0;
};

class IWorldBlock {
public:
	virtual Emiks* getId() = 0;
};

#endif //GLOBALQT_ILEVEL_H
