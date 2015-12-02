#include "ModLoader/core/level/mlevel.h"

//MLevelInfo
MLevelInfo::MLevelInfo(QString name) { this->name = name;}

QString MLevelInfo::getName() {	return this->name;}
QString MLevelInfo::getFile() {	return file;}

void MLevelInfo::setName(QString name) {	this->name = name;}
void MLevelInfo::setFile(QString file) { this->file = file;}
//MLevelInfo

//MLevel
MLevel::MLevel(ILevelInfo* info) {
	this->info = info;
	this->info->setFile("saves/"+info->getName()+"/dim0/");
	QDir().mkpath(this->info->getName());
}
QString MLevel::getName() { return info->getName(); }

void MLevel::load() {

}
void MLevel::save() {

}
void MLevel::saveInfo() {

}

IPChunk *MLevel::getPreview() {
	return new MPChunk();
}
void MLevel::cycleRegion() {

}
IChunk * MLevel::getChunk(IChunkPos pos) {

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

