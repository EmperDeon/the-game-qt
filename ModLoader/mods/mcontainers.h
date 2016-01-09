#ifndef GLOBALQT_MCONTAINERS_H
#define GLOBALQT_MCONTAINERS_H
#include <QtCore>
#include <ModLoader/mdefines.h>
#include <ModLoader/mmodloader.h>

class MMods;

// Items
class MIIds : public IModsIds {
 MMods* loader;
	QMap<QString, Imiks>* mods;
 Imiks mNull;

public:
 MIIds(MMods *m, QMap<QString, Imiks>* l);
	Imiks get(QString m, QString i, QString k, int s) override;
};

class MItem : public IItem{
	float stackSize;
	int stackType;

public:
	MItem(QJsonObject o);
	virtual float getStackSize() override;
	virtual int getStackType() override;
};

class MItemsContainer : public IItemsContainer{
	MMods* loader;
 QMap<Imiks, IItem*>* map;
 Imiks mNull;
	IItem* iNull;

public:
	MItemsContainer(MMods* l, QMap<Imiks, IItem*>* m);
 IItem* get(Imiks id) override;
	Imiks get(IItem* id) override;
};
// Items

// Blocks
class MBIds : public IModsIds {
	MMods* loader;
	QMap<QString, Imiks>* mods;
	Imiks mNull;

public:
	MBIds(MMods *m, QMap<QString, Imiks>* l);
	Imiks get(QString m, QString i, QString k, int s) override;
};

class MBlock : public IBlock{
	float weight;
public:
	MBlock(QJsonObject o);
	virtual float getWeight() override;
};

class MBlocksContainer : public IBlocksContainer{
	MMods* loader;
	QMap<Imiks, IBlock*>* map;
	Imiks mNull;
	IBlock* iNull;

public:
	MBlocksContainer(MMods* l, QMap<Imiks, IBlock*>* m);
	IBlock* get(Imiks id) override;
	Imiks get(IBlock* id) override;
};
// Blocks

// Tools
class MTIds : public IModsIds {
	MMods* loader;
	QMap<QString, Imiks>* mods;
	Imiks mNull;

public:
	MTIds(MMods *m, QMap<QString, Imiks>* l);
	Imiks get(QString m, QString i, QString k, int s) override;
};

class MTool : public ITool{
	int durability;
	QString type;

public:
	MTool(QJsonObject o);
	virtual int getDurability() override;
	virtual QString getType() override;
};

class MToolsContainer : public IToolsContainer{
	MMods* loader;
	QMap<Imiks, ITool*>* map;
	Imiks mNull;
	ITool* iNull;

public:
	MToolsContainer(MMods* l, QMap<Imiks, ITool*>* m);
	ITool* get(Imiks id) override;
	Imiks get(ITool* id) override;
};
// Tools

#endif //GLOBALQT_MCONTAINERS_H
