#ifndef GLOBALQT_MLEVEL_H
#define GLOBALQT_MLEVEL_H
#include <ModLoader/mdefines.h>
#include <ModLoader/core/level/mregion.h>

class MLevelInfo : public ILevelInfo{
	QString name;
	QString dir;
public:
	MLevelInfo();

	virtual static QJsonObject toJson(MLevelInfo *info);
	virtual static ILevelInfo * fromJson(QJsonObject obj);

	virtual QString getName();
	virtual QString getDir();

	virtual void setName(QString name);
	virtual void setDir(QString file);
};

class MLevel : public ILevel{
	MRegion* reg;
	ILevelInfo* info;

 QMap<IChunkPos, IChunk*>* chunkList;


public:
	MLevel(ILevelInfo* info);
	virtual QString getName();
	virtual void load();
	void load(QJsonObject obj);
	virtual void save();
 virtual void saveInfo();

	virtual IPChunk * getPreview();
	virtual void cycleRegion();
	virtual IChunk *getChunk(IChunkPos pos);
};

class MLevelManager : public ILevelManager{
	QList<ILevelInfo*> list;
	ILevelInfo* current;
 ILevel* level;

public:
	virtual QList<ILevelInfo*> getList();
	virtual ILevel* getCurrentLevel();
	virtual ILevelInfo* getCurrentLevelInfo();
	virtual void createLevel(ILevelInfo* i);
	virtual void exitLevel(ILevelInfo* i);
	virtual void removeLevel(ILevelInfo* i);
};

#endif //GLOBALQT_MLEVEL_H
