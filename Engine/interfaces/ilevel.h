#ifndef GLOBALQT_ILEVEL_H
#define GLOBALQT_ILEVEL_H
class Imiks;

class IWorldBlock {
public:
	virtual Imiks getId() = 0;
	virtual IBlockPos getPos() = 0;
	virtual QString getParams() = 0;
	virtual void addParam(QString s) = 0;
	virtual void setParam(QString s) = 0;
	virtual bool isParams() = 0;
};

class IChunk{
public:
	virtual IChunkPos getId() = 0;
	virtual void setBlock(IWorldBlock* b) = 0;
	virtual IWorldBlock* getBlock(IBlockPos p) = 0;
};

class IRegion{
public:
	virtual IRegionPos getId() = 0;
	virtual IChunk* getChunk(IChunkPos p) = 0;
};

class ILevel{
public:
	virtual QString getName() = 0;
	virtual void load() = 0;
	virtual void save() = 0;

};
#endif //GLOBALQT_ILEVEL_H
