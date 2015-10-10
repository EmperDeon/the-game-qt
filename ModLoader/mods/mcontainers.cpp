#include <ModLoader/mods/mcontainers.h>

MIIds::MIIds(MMods *m, QMap<QString, Emiks*>* l) {
 this->loader = m;
	this->mods = l;
	this->mnull = new Emiks(0,0,0,0);
}
Emiks*MIIds::get(QString m, QString i, QString k, int s) {
	QString t = m+"^"+i+"^"+k+"^"+QString::number(s);
	if(mods->contains(t))
  return mods->value(t);
	else{
		loader->log->log(GLogLevel::ERR, "MIIds","Map doesn't contains "+t+", unexpected result (returning 0,0,0,0)");
		return mnull;
	}
}

MItem::MItem(QJsonObject o) {
	this->stackSize = o["stackSize"].toDouble(1.0);
	this->stackType = o["stackType"].toInt(1);
}
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

MBIds::MBIds(MMods *m, QMap<QString, Emiks*>* l){
	this->loader = m;
	this->mods = l;
	this->mnull = new Emiks(0,0,0,0);
}
Emiks*MBIds::get(QString m, QString i, QString k, int s) {
	QString t = m+"^"+i+"^"+k+"^"+QString::number(s);
	if(mods->contains(t))
		return mods->value(t);
	else{
		loader->log->log(GLogLevel::ERR, "MIIds","Map doesn't contains "+t+", unexpected result (returning 0,0,0,0)");
		return mnull;
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


MTIds::MTIds(MMods *m, QMap<QString, Emiks*>* l) {
	this->loader = m;
	this->mods = l;
	this->mnull = new Emiks(0,0,0,0);
}
Emiks*MTIds::get(QString m, QString i, QString k, int s) {
	QString t = m+"^"+i+"^"+k+"^"+QString::number(s);
	if(mods->contains(t))
		return mods->value(t);
	else{
		loader->log->log(GLogLevel::ERR, "MTIds","Map doesn't contains "+t+", unexpected result (returning 0,0,0,0)");
		return mnull;
	}
}

MTool::MTool(QJsonObject o) {
	this->durability = o["drb"].toInt(0);
	this->type = o["type"].toString("item");
}
int MTool::getDurability() {	return durability;}
QString MTool::getType() {	return type;}

MToolsContainer::MToolsContainer(MMods *l, QMap<Emiks *, ITool *> *m) {
	this->loader = l;
	this->map = m;
	this->mNull = new Emiks(0,0,0,0);
	this->iNull = new MTool(QJsonObject());
}
ITool *MToolsContainer::get(Emiks *id) {
	if(map->contains(id))
		return map->value(id);
	else {
		loader->log->log(GLogLevel::ERR, "MToolsContainer", "Map doesn't contains id, unexpected result (returning 0,0,0,0)");
		return iNull;
	}
}
Emiks *MToolsContainer::get(ITool *id) {
	if(map->values().contains(id))
		return map->key(id);
	else{
		loader->log->log(GLogLevel::ERR, "MToolsContainer","Map doesn't contains id, unexpected result (returning 0,0,0,0)");
		return mNull;
	}
}