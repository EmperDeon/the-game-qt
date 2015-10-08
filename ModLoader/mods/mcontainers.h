#ifndef GLOBALQT_MCONTAINERS_H
#define GLOBALQT_MCONTAINERS_H

#include <QtCore>
#include <Global/gmodinterfaces.h>
#include <ModLoader/mmodloader.h>
#include <wingdi.h>

class MMods;

class MIds : public IModsIds {
 Q_INTERFACES(IItemIds)
 MMods* loader;
	QMap<QString, Emiks*>* mods;
 Emiks* mnull;

public:
 MIds(MMods *m, QMap<QString, Emiks*>* l);
	Emiks* get(QString m, QString i, QString k, int s) Q_DECL_OVERRIDE;
};

class MItem : public IItem{
	int durability;
	QString type;
	float stackSize;
	int stackType;

public:
	MItem(QJsonObject o);
	int getDurability() Q_DECL_OVERRIDE;
	QString getType() Q_DECL_OVERRIDE;
	float getStackSize() Q_DECL_OVERRIDE;
	int getStackType() Q_DECL_OVERRIDE;
};
class MItemsContainer : public IItemsContainer{
	Q_INTERFACES(IItemsContainer)
	MMods* loader;
 QMap<Emiks*, IItem*>* map;
 Emiks* mNull;
	IItem* iNull;

public:
	MItemsContainer(MMods* l, QMap<Emiks*, IItem*>* m);
 IItem* get(Emiks* id) Q_DECL_OVERRIDE;
	Emiks* get(IItem* id) Q_DECL_OVERRIDE;
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
	QMap<Emiks*, IBlock*>* map;
	Emiks* mNull;
	IBlock* iNull;

public:
	MBlocksContainer(MMods* l, QMap<Emiks*, IBlock*>* m);
	IBlock* get(Emiks* id) Q_DECL_OVERRIDE;
	Emiks* get(IBlock* id) Q_DECL_OVERRIDE;
};
#endif //GLOBALQT_MCONTAINERS_H
