#ifndef GLOBALQT_MLEVEL_H
#define GLOBALQT_MLEVEL_H
#include <ModLoader/mdefines.h>
#include <ModLoader/core/level/mregion.h>
#include <ModLoader/core/level/mgenerator.h>

class MLevelInfo : public ILevelInfo{
	QString name;
	QString dir;
	QJsonObject* custom;

public:
	MLevelInfo();

	static QJsonObject toJson(MLevelInfo *info);
	static ILevelInfo * fromJson(QJsonObject obj);

	virtual QString getName() override {return name;}
	virtual QString getDir()  override {return dir;}

	virtual void setName(QString name) override {this->name = name;}
	virtual void setDir(QString file)  override {this->dir = file;}

	virtual void         addCustom(QJsonObject)                     override;
	virtual QJsonObject* getCustom()                                override {return custom;}
	virtual QJsonValue   getFromCustom(QString key)                 override {return custom->value(key);}
	virtual void         addToCustom(QString key, QJsonValue value) override {custom->insert(key, value);}
};

class MLevel : public ILevel{
	MRegion* reg;
	ILevelInfo* info;
 MWorldGenerator* generator;
 QMap<IChunkPos, IChunk*>* chunkList;

	void loadChunk(IChunkPos pos, QJsonObject obj, QDataStream &stream);

public:
	MLevel(ILevelInfo* info);

	virtual QString getName()                  override {return info->getName();}
	virtual void load()                        override;
	virtual void save()                        override;
	virtual void generateWorld()               override;
	virtual void reAllocate(IWorldRender *ren) override;
	virtual bool isBlock(IVec3i p)             override;

	virtual IPChunk* getPreview()            override;
	virtual void     cycleRegion()           override;
	virtual IChunk*  getChunk(IChunkPos pos) override;

	void addNewChunk(IChunkPos c);
};

class MLevelManager : public ILevelManager{
	QList<ILevelInfo*>* list;
	ILevelInfo* current;
 ILevel* level;

public:
	MLevelManager();

	virtual QList<ILevelInfo*>* getList()             override {return list;}
	virtual ILevel*             getCurrentLevel()     override {return level;}
	virtual ILevelInfo*         getCurrentLevelInfo() override {return current;}

	virtual void createLevel(ILevelInfo* i) override;
	virtual void loadLevel(ILevelInfo* i)   override;
	virtual void exitLevel(ILevelInfo* i)   override;
	virtual void removeLevel(ILevelInfo* i) override;
};

#endif //GLOBALQT_MLEVEL_H
