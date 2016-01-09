#ifndef GLOBALQT_MCONTAINERS_H
#define GLOBALQT_MCONTAINERS_H

#include <QtCore>
#include <ModLoader/mdefines.h>
#include <ModLoader/mmodloader.h>

class MMods;

// Items
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
	QString tex;
	float stackSize;
	int stackType;

public:
	MItem(QJsonObject o);
	virtual float getStackSize() override;
	virtual int getStackType() override;

	virtual QString getTexture() override;
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
// Items

// Blocks
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
	QString tex;
	float weight;
public:
	MBlock(QJsonObject o);
	virtual float getWeight() override;

	virtual QString getTexture() override;
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
// Blocks

// Tools
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
	QString tex;
	int durability;
	QString type;

public:
	MTool(QJsonObject o);
	virtual int getDurability() override;
	virtual QString getType() override;

	virtual QString getTexture() override;
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
// Tools

#endif //GLOBALQT_MCONTAINERS_H
