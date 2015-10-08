#include <ModLoader/mods/mcontainers.h>

MIds::MIds(MMods *m, QMap<QString, Emiks*>* l) {
 this->loader = m;
	this->mods = l;
	this->mnull = new Emiks(0,0,0,0);
}
Emiks* MIds::get(QString m, QString i, QString k, int s) {
	QString t = m+"^"+i+"^"+k+"^"+QString::number(s);
	if(mods->contains(t))
  return mods->value(t);
	else{
		loader->log->log(GLogLevel::ERR, "MIds","Map doesn't contains "+t+", unexpected result (returning 0,0,0,0)");
		return mnull;
	}
}

MItem::MItem(QJsonObject o) {
 this->durability = o["drb"].toInt(0);
	this->type = o["type"].toString("item");
	this->stackSize = o["stackSize"].toDouble(1.0);
	this->stackType = o["stackType"].toInt(1);
}
int MItem::getDurability() {	return durability;}
QString MItem::getType() {	return type;}
float MItem::getStackSize() {	return stackSize;}
int MItem::getStackType() {	return stackType;}

MItemsContainer::MItemsContainer(MMods *l, QMap<Emiks *, IItem *> *m) {
 this->loader = l;
	this->map = m;
	this->mNull = new Emiks(0,0,0,0);
	this->iNull = new MItem(QJsonObject());
}
IItem *MItemsContainer::get(Emiks *id) {
 if(map->contains(id))
	 return map->value(id);
 else {
	 loader->log->log(GLogLevel::ERR, "MItemsContainer", "Map doesn't contains id, unexpected result (returning 0,0,0,0)");
	 return iNull;
 }
}
Emiks *MItemsContainer::get(IItem *id) {
 if(map->values().contains(id))
	 return map->key(id);
 else{
	 loader->log->log(GLogLevel::ERR, "MItemsContainer","Map doesn't contains id, unexpected result (returning 0,0,0,0)");
	 return mNull;
 }
}

MBlock::MBlock(QJsonObject o) {
 weight = 0.0;
}
float MBlock::getWeight() {
	return 0;
}

MBlocksContainer::MBlocksContainer(MMods *l, QMap<Emiks *, IBlock *> *m) {
	this->loader = l;
	this->map = m;
	this->mNull = new Emiks(0,0,0,0);
	this->iNull = new MBlock(QJsonObject());
}
IBlock* MBlocksContainer::get(Emiks *id) {
	if(map->contains(id))
		return map->value(id);
	else {
		loader->log->log(GLogLevel::ERR, "MBlocksContainer", "Map doesn't contains id, unexpected result (returning 0,0,0,0)");
		return iNull;
	}
}
Emiks *MBlocksContainer::get(IBlock *id) {
	if(map->values().contains(id))
		return map->key(id);
	else{
		loader->log->log(GLogLevel::ERR, "MBlocksContainer","Map doesn't contains id, unexpected result (returning 0,0,0,0)");
		return mNull;
	}
}


