#include "ModLoader/core/level/mlevel.h"

//MLevelInfo
MLevelInfo::MLevelInfo(){}

QString MLevelInfo::getName() {	return this->name;}
QString MLevelInfo::getDir() {	return dir;}

void MLevelInfo::setName(QString name) {	this->name = name;}
void MLevelInfo::setDir(QString file) { this->dir = file;}

QJsonObject MLevelInfo::toJson(MLevelInfo *info) {
	QJsonObject obj;

	obj["name"] = info->name;
	obj["dir"] = info->dir;

	return obj;
}

ILevelInfo * MLevelInfo::fromJson(QJsonObject obj) {
	MLevelInfo* info = new MLevelInfo();

	info->name = obj.value("name").toString();
	info->dir = obj.value("dir").toString();

	return info;
}
//MLevelInfo

//MLevel
MLevel::MLevel(ILevelInfo* info) {
	this->info = info;
	this->info->setDir("saves/" + info->getName() + "/");
	QDir().mkpath(this->info->getDir());

	this->chunkList = new QMap<IChunkPos, IChunk*>;
}
QString MLevel::getName() { return info->getName(); }

void MLevel::load() {
	load(QJsonDocument::fromBinaryData(QFile(info->getDir()+"level.dat").readAll()).object());
}
void MLevel::load(QJsonObject obj) {

}
void MLevel::save() {
 saveInfo();
}
void MLevel::saveInfo() {
 QJsonObject obj = MLevelInfo::toJson(reinterpret_cast<MLevelInfo*>(this->info));

	QJsonArray ids;
	foreach(IChunkPos p, this->chunkList->keys()){
	 ids.append(p.c());
	}
	obj["chunkIds"] = ids;

	QFile out(info->getDir()+"level.dat");
	out.write(QJsonDocument(obj).toBinaryData());
	out.flush();
	out.close();
}

IPChunk *MLevel::getPreview() {	return new MPChunk();}
void MLevel::cycleRegion() {}
IChunk * MLevel::getChunk(IChunkPos pos) {
 if(this->chunkList->contains(pos)){
	 return this->chunkList->value(pos);
 }else{
	 return new MChunk();
 }
}
//MLevel

//MLevelManager
QList<ILevelInfo*> MLevelManager::getList() {	return this->list;}
ILevel* MLevelManager::getCurrentLevel() {	return this->level;}
ILevelInfo* MLevelManager::getCurrentLevelInfo() {	return this->current;}

void MLevelManager::createLevel(ILevelInfo* i) {
 this->current = i;

 this->level = new MLevel(this->current);
	this->level->saveInfo();
}
void MLevelManager::exitLevel(ILevelInfo* i) {
 this->level->save();
}
void MLevelManager::removeLevel(ILevelInfo* i) {

}



