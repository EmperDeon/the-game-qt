#ifndef GLOBALQT_MCONTAINERS_H
#define GLOBALQT_MCONTAINERS_H
#include <idefines.h>

// Items
class MIIds : public IModsIds {
	QMap<QString, Imiks>* mods;
 Imiks mNull;

public:
 MIIds(QMap<QString, Imiks>* l);

	Imiks get(QString m, QString i, QString k, int s) override;
};

class MItem : public IItem{
	float stackSize;
	int stackType;

public:
	MItem(QJsonObject o);

	virtual float getStackSize() override {return stackSize;}
	virtual int   getStackType() override {return stackType;}
};

class MItemsContainer : public IItemsContainer{
 QMap<Imiks, IItem*>* map;
 Imiks mNull;
	IItem* iNull;

public:
	MItemsContainer(QMap<Imiks, IItem*>* m);

 virtual IItem* get(Imiks id) override;
	virtual Imiks get(IItem* id) override;
};
// Items

// Blocks
class MBIds : public IModsIds {
	QMap<QString, Imiks>* mods;
	Imiks mNull;

public:
	MBIds(QMap<QString, Imiks>* l);

	Imiks get(QString m, QString i, QString k, int s) override;
};

class MBlock : public IBlock{
	float weight;
public:
	MBlock(QJsonObject o);

	virtual float getWeight() override {return weight;}
};

class MBlocksContainer : public IBlocksContainer{
	QMap<Imiks, IBlock*>* map;
	Imiks mNull;
	IBlock* iNull;

public:
	MBlocksContainer(QMap<Imiks, IBlock*>* m);

	IBlock* get(Imiks id) override;
	Imiks get(IBlock* id) override;
};
// Blocks

// Tools
class MTIds : public IModsIds {
	QMap<QString, Imiks>* mods;
	Imiks mNull;

public:
	MTIds(QMap<QString, Imiks>* l);

	Imiks get(QString m, QString i, QString k, int s) override;
};

class MTool : public ITool{
	int durability;
	QString type;

public:
	MTool(QJsonObject o);
	virtual int     getDurability() override {return durability;}
	virtual QString getType()       override {return type;}
};

class MToolsContainer : public IToolsContainer{
	QMap<Imiks, ITool*>* map;
	Imiks mNull;
	ITool* iNull;

public:
	MToolsContainer(QMap<Imiks, ITool*>* m);

	ITool* get(Imiks id) override;
	Imiks get(ITool* id) override;
};
// Tools

#endif //GLOBALQT_MCONTAINERS_H
