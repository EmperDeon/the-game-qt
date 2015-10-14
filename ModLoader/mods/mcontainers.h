#ifndef GLOBALQT_MCONTAINERS_H
#define GLOBALQT_MCONTAINERS_H

#include <QtCore>
#include <ModLoader/mdefines.h>
#include "einterfaces.h"
#include <ModLoader/mmodloader.h>

class MMods;

class MIIds : public IModsIds {
 Q_INTERFACES(IItemIds)
 MMods* loader;
	QString className = "M-IIds";
	QMap<QString, Imiks>* mods;
 Imiks mnull;

public:
 MIIds(MMods *m, QMap<QString, Imiks>* l);
	Imiks get(QString m, QString i, QString k, int s) Q_DECL_OVERRIDE;
};
class MItem : public IItem{
	float stackSize;
	int stackType;

public:
	MItem(QJsonObject o);
	float getStackSize() Q_DECL_OVERRIDE;
	int getStackType() Q_DECL_OVERRIDE;
};
class MItemsContainer : public IItemsContainer{
	Q_INTERFACES(IItemsContainer)
	MMods* loader;
	QString className = "M-ItemsContainer";
 QMap<Imiks, IItem*>* map;
 Imiks mNull;
	IItem* iNull;

public:
	MItemsContainer(MMods* l, QMap<Imiks, IItem*>* m);
 IItem* get(Imiks id) Q_DECL_OVERRIDE;
	Imiks get(IItem* id) Q_DECL_OVERRIDE;
};

class MBIds : public IModsIds {
	Q_INTERFACES(IItemIds)
	MMods* loader;
	QString className = "M-BIds";
	QMap<QString, Imiks>* mods;
	Imiks mnull;

public:
	MBIds(MMods *m, QMap<QString, Imiks>* l);
	Imiks get(QString m, QString i, QString k, int s) Q_DECL_OVERRIDE;
};
class MBlock : public IBlock{
	float weight;
public:
	MBlock(QJsonObject o);
	float getWeight() Q_DECL_OVERRIDE;
};
class MBlocksContainer : public IBlocksContainer{
	Q_INTERFACES(IBlocksContainer)
	MMods* loader;
	QString className = "M-BlocksContainer";
	QMap<Imiks, IBlock*>* map;
	Imiks mNull;
	IBlock* iNull;

public:
	MBlocksContainer(MMods* l, QMap<Imiks, IBlock*>* m);
	IBlock* get(Imiks id) Q_DECL_OVERRIDE;
	Imiks get(IBlock* id) Q_DECL_OVERRIDE;
};

class MTIds : public IModsIds {
	Q_INTERFACES(IItemIds)
	MMods* loader;
	QString className = "M-TIds";
	QMap<QString, Imiks>* mods;
	Imiks mnull;

public:
	MTIds(MMods *m, QMap<QString, Imiks>* l);
	Imiks get(QString m, QString i, QString k, int s) Q_DECL_OVERRIDE;
};
class MTool : public ITool{
	int durability;
	QString type;

public:
	MTool(QJsonObject o);
	int getDurability() Q_DECL_OVERRIDE;
	QString getType() Q_DECL_OVERRIDE;
};
class MToolsContainer : public IToolsContainer{
	Q_INTERFACES(IToolsContainer)
	MMods* loader;
	QString className = "M-ToolsContainer";
	QMap<Imiks, ITool*>* map;
	Imiks mNull;
	ITool* iNull;

public:
	MToolsContainer(MMods* l, QMap<Imiks, ITool*>* m);
	ITool* get(Imiks id) Q_DECL_OVERRIDE;
	Imiks get(ITool* id) Q_DECL_OVERRIDE;
};

#endif //GLOBALQT_MCONTAINERS_H
