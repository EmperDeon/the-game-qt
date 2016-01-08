#ifndef GLOBALQT_MLEVEL_H
#define GLOBALQT_MLEVEL_H
#include <ModLoader/mdefines.h>
#include <ModLoader/core/level/mregion.h>
#include <ModLoader/core/level/mgenerator.h>
#include <ModLoader/core/mcoremods.h>

class MCoreMods;

class MLevelInfo : public ILevelInfo{
	QString name;
	QString dir;
	QJsonObject* custom;

public:
	MLevelInfo();

	static QJsonObject toJson(MLevelInfo *info);
	static ILevelInfo * fromJson(QJsonObject obj);

	virtual QString getName();
	virtual QString getDir();

	virtual void setName(QString name);
	virtual void setDir(QString file);

	virtual QJsonObject *getCustom();
	virtual void addCustom(QJsonObject);
	virtual QJsonValue getFromCustom(QString key);
	virtual void addToCustom(QString key, QJsonValue value);
};

class MLevel : public ILevel{
	MRegion* reg;
	ILevelInfo* info;
 MWorldGenerator* generator;
 QMap<IChunkPos, IChunk*>* chunkList;


public:
	MLevel(ILevelInfo* info);
	virtual QString getName();
	virtual void load();
	virtual void save();
	virtual void generateWorld();
	virtual void reAllocate(IWorldRender *ren);
	virtual bool isBlock(IVec3i p);

	virtual IPChunk * getPreview();
	virtual void cycleRegion();
	virtual IChunk *getChunk(IChunkPos pos);

	void addNewChunk(IChunkPos c);
private:
 void loadChunk(IChunkPos pos, QJsonObject obj, QDataStream &stream);
};

class MLevelManager : public ILevelManager{
	QList<ILevelInfo*>* list;
	ILevelInfo* current;
 ILevel* level;

	QString className = "MLevelManager";
	MCoreMods* loader;
public:
	MLevelManager(MCoreMods* m);
	virtual QList<ILevelInfo*>* getList();
	virtual ILevel* getCurrentLevel();
	virtual ILevelInfo* getCurrentLevelInfo();
	virtual void createLevel(ILevelInfo* i);
	virtual void loadLevel(ILevelInfo* i);
	virtual void exitLevel(ILevelInfo* i);
	virtual void removeLevel(ILevelInfo* i);
};

#endif //GLOBALQT_MLEVEL_H
