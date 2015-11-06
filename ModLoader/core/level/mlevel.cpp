#include "ModLoader/core/level/mlevel.h"

MLevel::MLevel(QString name) {
 this->name = "saves/"+name+"/dim0/";
	QDir().mkpath(this->name);
	this->reg = new MRegion(IRegionPos(0,0), this->name);
}
QString MLevel::getName() {
 return name;
}

void MLevel::load() {
 reg->read();
}

void MLevel::save() {
 reg->write();
}


