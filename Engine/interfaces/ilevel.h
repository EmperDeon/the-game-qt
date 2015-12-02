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

class IPChunk{// Prewiew
public:
 virtual QColor getBlockColor(IBlockPos pos) = 0;
};

class IRegion{
public:
	virtual IRegionPos getId() = 0;
	virtual IChunk* getChunk(IChunkPos p) = 0;
};

class ILevelInfo{
public:
	virtual QString getName() = 0;
	virtual QString getDir() = 0;

	virtual void setName(QString name) = 0;
	virtual void setDir(QString file) = 0;
};

class ILevel{
public:
	virtual QString getName() = 0;
	virtual void load() = 0;
	virtual void save() = 0;
	virtual void saveInfo() = 0;

	virtual IPChunk * getPreview() = 0;
	virtual void cycleRegion() = 0;
	virtual IChunk * getChunk(IChunkPos pos) = 0;
};

class ILevelManager{
public:
	virtual QList<ILevelInfo*> getList() = 0;
	virtual ILevel* getCurrentLevel() = 0;
	virtual ILevelInfo* getCurrentLevelInfo() = 0;
	virtual void createLevel(ILevelInfo* i) = 0;
	virtual void exitLevel(ILevelInfo* i) = 0;
	virtual void removeLevel(ILevelInfo* i) = 0;
};
#endif //GLOBALQT_ILEVEL_H
