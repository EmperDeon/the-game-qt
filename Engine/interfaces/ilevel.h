#ifndef GLOBALQT_ILEVEL_H
#define GLOBALQT_ILEVEL_H
class Imiks;

class IWorldBlock {
public:
	virtual Imiks getId() = 0;
	virtual IBlockPos getPos() = 0;
	virtual int getPCount() = 0;
};

class IRegon{

};

class IChunk{
public:
	virtual IWorldBlock getBlock(IBlockPos p) = 0;
	virtual QString getParams(IWorldBlock b) = 0;
	virtual void load(QDataStream& a) = 0;
	virtual void save(QDataStream& a) = 0;
};


#endif //GLOBALQT_ILEVEL_H
