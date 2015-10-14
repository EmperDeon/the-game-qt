#include <ModLoader/mods/mcontainers.h>

MIIds::MIIds(MMods *m, QMap<QString, Imiks>* l) : loader(m), mods(l), mnull(0,0,0,0){}
Imiks MIIds::get(QString m, QString i, QString k, int s) {
	QString t = m+"^"+i+"^"+k+"^"+QString::number(s);
	if(mods->contains(t))
  return mods->value(t);
	else{
		mLogE("Map doesn't contains "+t+", unexpected result (returning 0,0,0,0)");
		return mnull;
	}
}

MItem::MItem(QJsonObject o) {
	this->stackSize = o["stackSize"].toDouble(1.0);
	this->stackType = o["stackType"].toInt(1);
}
float MItem::getStackSize() {	return stackSize;}
int MItem::getStackType() {	return stackType;}

MItemsContainer::MItemsContainer(MMods *l, QMap<Imiks, IItem *> *m) : loader(l), map(m), mNull(0,0,0,0){
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

MBIds::MBIds(MMods *m, QMap<QString, Imiks>* l) : loader(m), mods(l), mnull(0,0,0,0){}
Imiks MBIds::get(QString m, QString i, QString k, int s) {
	QString t = m+"^"+i+"^"+k+"^"+QString::number(s);
	if(mods->contains(t))
		return mods->value(t);
	else{
		mLogE("Map doesn't contains "+t+", unexpected result (returning 0,0,0,0)");
		return mnull;
	}
}


MBlock::MBlock(QJsonObject o) {
 weight = 0.0;
}
float MBlock::getWeight() {
	return 0;
}

MBlocksContainer::MBlocksContainer(MMods *l, QMap<Imiks, IBlock *> *m) : loader(l), map(m), mNull(0,0,0,0){
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


MTIds::MTIds(MMods *m, QMap<QString, Imiks>* l) : loader(m), mods(l), mnull(0,0,0,0) {}
Imiks MTIds::get(QString m, QString i, QString k, int s) {
	QString t = m+"^"+i+"^"+k+"^"+QString::number(s);
	if(mods->contains(t))
		return mods->value(t);
	else{
		mLogE("Map doesn't contains "+t+", unexpected result (returning 0,0,0,0)");
		return mnull;
	}
}

MTool::MTool(QJsonObject o) {
	this->durability = o["drb"].toInt(0);
	this->type = o["type"].toString("item");
}
int MTool::getDurability() {	return durability;}
QString MTool::getType() {	return type;}

MToolsContainer::MToolsContainer(MMods *l, QMap<Imiks, ITool *> *m) : loader(l), map(m), mNull(0,0,0,0) {
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