#include <ModLoader/mods/mcontainers.h>

// MIdis
MIIds::MIIds(QMap<QString, Imiks>* l) : mods(l), mNull(0, 0, 0, 0){}

Imiks MIIds::get(QString m, QString i, QString k, int s) {
	QString t = m+"^"+i+"^"+k+"^"+QString::number(s);
	if(mods->contains(t))
  return mods->value(t);
	else{
		mLogE("Map doesn't contains "+t+", unexpected result (returning 0,0,0,0)");
		return mNull;
	}
}
// MIds


// MItem
MItem::MItem(QJsonObject o) {
	this->stackSize = (float)o["stackSize"].toDouble(1.0);
	this->stackType = o["stackType"].toInt(1);
}
// MItem


// MItemsContainer
MItemsContainer::MItemsContainer(QMap<Imiks, IItem *> *m) :  map(m), mNull(0,0,0,0){
	this->iNull = new MItem(QJsonObject());
}

IItem *MItemsContainer::get(Imiks id) {
 if(map->contains(id))
	 return map->value(id);
 else {
	 mLogE("Map doesn't contains id, unexpected result (returning 0,0,0,0)");
	 return iNull;
 }
}

Imiks MItemsContainer::get(IItem* id) {
 if(map->values().contains(id))
	 return map->key(id);
 else{
	 mLogE("Map doesn't contains id, unexpected result (returning 0,0,0,0)");
	 return mNull;
 }
}
// MItemsContainer


// MBIds
MBIds::MBIds(QMap<QString, Imiks>* l) : mods(l), mNull(0, 0, 0, 0){}

Imiks MBIds::get(QString m, QString i, QString k, int s) {
	QString t = m+"^"+i+"^"+k+"^"+QString::number(s);
	if(mods->contains(t))
		return mods->value(t);
	else{
		mLogE("Map doesn't contains "+t+", unexpected result (returning 0,0,0,0)");
		return mNull;
	}
}
// MBIds


// MBlock
MBlock::MBlock(QJsonObject o) {
 this->weight = (float)o["weight"].toDouble();
}
// MBlock


// MBlocksContainer
MBlocksContainer::MBlocksContainer(QMap<Imiks, IBlock *> *m) :map(m), mNull(0,0,0,0){
	this->iNull = new MBlock(QJsonObject());
}

IBlock* MBlocksContainer::get(Imiks id) {
	if(map->contains(id))
		return map->value(id);
	else {
		mLogE("Map doesn't contains id, unexpected result (returning 0,0,0,0)");
		return iNull;
	}
}

Imiks  MBlocksContainer::get(IBlock *id) {
	if(map->values().contains(id))
		return map->key(id);
	else{
		mLogE("Map doesn't contains id, unexpected result (returning 0,0,0,0)");
		return mNull;
	}
}
// MBlockContainer


// MTIds
MTIds::MTIds(QMap<QString, Imiks>* l) : mods(l), mNull(0, 0, 0, 0) {}

Imiks MTIds::get(QString m, QString i, QString k, int s) {
	QString t = m+"^"+i+"^"+k+"^"+QString::number(s);
	if(mods->contains(t))
		return mods->value(t);
	else{
		mLogE("Map doesn't contains "+t+", unexpected result (returning 0,0,0,0)");
		return mNull;
	}
}
// MTIds


// MTool
MTool::MTool(QJsonObject o) {
	this->durability = o["drb"].toInt(0);
	this->type = o["type"].toString("item");
}
// MTool


// MToolsContainer
MToolsContainer::MToolsContainer(QMap<Imiks, ITool *> *m) : map(m), mNull(0,0,0,0) {
	this->iNull = new MTool(QJsonObject());
}

ITool *MToolsContainer::get(Imiks id) {
	if(map->contains(id))
		return map->value(id);
	else {
		mLogE("Map doesn't contains id, unexpected result (returning 0,0,0,0)");
		return iNull;
	}
}

Imiks MToolsContainer::get(ITool *id) {
	if(map->values().contains(id))
		return map->key(id);
	else{
		mLogE("Map doesn't contains id, unexpected result (returning 0,0,0,0)");
		return mNull;
	}
}
// MToolsContainer

