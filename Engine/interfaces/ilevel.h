#ifndef GLOBALQT_ILEVEL_H
#define GLOBALQT_ILEVEL_H
#include "irender.h"
#include "iutils.h"


class Imiks;
class IRObject;
class IBlockPos;
class IChunkPos;
class IRegionPos;
class IVec3i;

// Blocks
class IWorldBlock {
public:
	virtual Imiks getId() = 0;
	virtual IBlockPos getPos() = 0;
	virtual QString getParams() = 0;
	virtual void addParam(QString s) = 0;
	virtual void setParam(QString s) = 0;
	virtual bool isParams() = 0;
};
// Blocks

// Chunks
class IChunk : public IRObject{
public:
	static const int size = 32;
	virtual IChunkPos getId() = 0;
	virtual void setBlock(IWorldBlock* b) = 0;
	virtual void setBlock(IBlockPos, IWorldBlock *b) = 0;
	virtual IWorldBlock* getBlock(IBlockPos) = 0;
	virtual void write(QDataStream &a, QJsonObject& o) = 0;
};
class IPChunk : public IRObject{// Prewiew
public:
 virtual QColor getBlockColor(IBlockPos) = 0;
};
// Chunks

// Regions
class IRegion{
public:
	virtual IRegionPos getId() = 0;
	virtual IChunk* getChunk(IChunkPos) = 0;
};
// Regions

// Level
class ILevelInfo{
public:
	virtual QString getName() = 0;
	virtual QString getDir() = 0;

	virtual void setName(QString name) = 0;
	virtual void setDir(QString file) = 0;

	//Customs
	virtual QJsonObject * getCustom() = 0;
	virtual void addCustom(QJsonObject) = 0;

	virtual QJsonValue getFromCustom(QString key) = 0;
	virtual void addToCustom(QString key, QJsonValue value) = 0;
};
class ILevel{
public:
	virtual QString getName() = 0;
	virtual void load() = 0;
	virtual void save() = 0;
	virtual void generateWorld() = 0;
 virtual void reAllocate(IWorldRender *ren) = 0;
 virtual bool isBlock(IVec3i) = 0;

	virtual IPChunk * getPreview() = 0;
	virtual void cycleRegion() = 0;
	virtual IChunk * getChunk(IChunkPos) = 0;
};
class ILevelManager {
public:
	virtual QList<ILevelInfo*>* getList() = 0;
	virtual ILevel* getCurrentLevel() = 0;
	virtual ILevelInfo* getCurrentLevelInfo() = 0;
	virtual void createLevel(ILevelInfo* i) = 0;
	virtual void loadLevel(ILevelInfo* i) = 0;
	virtual void exitLevel(ILevelInfo* i) = 0;
	virtual void removeLevel(ILevelInfo* i) = 0;
};
// Level

// Generator
class IWorldGeneratorInfo{

};
class IWorldGenerator{
public:
	virtual void generateChunk(IChunk* ch) = 0;
};
class IWorldGeneratorManager{
public:
	virtual QList<IWorldGeneratorInfo*> getList()                                                = 0;
	virtual IWorldGenerator*            getCurrentGenerator()                                    = 0;
	virtual IWorldGeneratorInfo*        getCurrentGeneratorInfo()                                = 0;
	virtual void                        addGenerator(IWorldGeneratorInfo* i, IWorldGenerator* g) = 0;
	virtual void                        exitLevel(IWorldGeneratorInfo* i)                        = 0;
	virtual void                        removeLevel(IWorldGeneratorInfo* i)                      = 0;
};
// Generator
#endif //GLOBALQT_ILEVEL_H
