#include "ModLoader/core/level/mlevel.h"
#include <QtConcurrent/QtConcurrent>
#include <iostream>
//MLevelInfo
MLevelInfo::MLevelInfo(){this->custom = new QJsonObject;}

QString MLevelInfo::getName() {	return this->name;}
QString MLevelInfo::getDir() {	return dir;}

void MLevelInfo::setName(QString name) {	this->name = name;}
void MLevelInfo::setDir(QString file) { this->dir = file;}

QJsonObject MLevelInfo::toJson(MLevelInfo *info) {
	QJsonObject obj(*info->custom);
	obj["name"] = info->name;
	obj["dir"] = info->dir;

	return obj;
}
ILevelInfo * MLevelInfo::fromJson(QJsonObject obj) {
	MLevelInfo* info = new MLevelInfo();
	info->name = obj.value("name").toString();
	info->dir = obj.value("dir").toString();
 foreach(QString k, obj.keys()){
			if((k.compare("name") != 0)
			 ||(k.compare("dir")  != 0)
				)
				info->custom->insert(k, obj.value(k));
		}
	return info;
}

QJsonObject * MLevelInfo::getCustom() {	return custom;}
void MLevelInfo::addCustom(QJsonObject object) {
		foreach(QString s, object.keys()){
			this->custom->insert(s, object.value(s));
		}
}
QJsonValue MLevelInfo::getFromCustom(QString key){ return this->custom->value(key);}
void MLevelInfo::addToCustom(QString key, QJsonValue value) { this->custom->insert(key, value);}
//MLevelInfo

//MLevel
MLevel::MLevel(ILevelInfo* info) {
	this->info = info;
	this->info->setDir("saves/" + info->getName() + "/");
	QDir().mkpath(this->info->getDir());

	this->chunkList = new QMap<IChunkPos, IChunk*>;
	this->generator = new MWorldGenerator;
}
QString MLevel::getName() { return info->getName(); }

void MLevel::load() {
	QFile file(info->getDir()+"chunks.dat");
	file.open(QIODevice::ReadOnly);
 QByteArray arr = qUncompress(file.readAll());
	QDataStream in(&arr, QIODevice::ReadOnly);
	QJsonObject obj = info->getFromCustom("chunks").toObject();
	QJsonArray ids = info->getFromCustom("chunkIds").toArray();

		foreach(QJsonValue v, ids) loadChunk(IChunkPos(quint16(v.toInt())), obj, in);

}
void MLevel::loadChunk(IChunkPos pos, QJsonObject obj, QDataStream &in) {
	int size = 262144;
	char* ch;

	ch = new char[size];
	in.skipRawData(4);
	in.readRawData(ch, size);

	chunkList->insert(pos,  new MChunk(
		QByteArray(ch, size),
		obj["chunk"+QString::number(pos.x())+QString::number(pos.y())+QString::number(pos.z())].toObject(),
		pos
	));

	delete[] ch;

}
void MLevel::save() {
	QJsonArray ids;
	QJsonObject obj;
	QByteArray arr;
	QDataStream stream(&arr, QIODevice::WriteOnly);

		foreach(IChunkPos p, this->chunkList->keys())	ids.append(p.c());
	info->addToCustom("chunkIds", ids);

		foreach(IChunk* p, this->chunkList->values())	p->write(stream, obj);
	info->addToCustom("chunks", obj);

	QFile out(info->getDir()+"chunks.dat");
	out.open(QIODevice::WriteOnly);
	out.write(qCompress(arr));
	out.flush();
	out.close();

	QFile out1(info->getDir()+"level.dat");
	out1.open(QIODevice::WriteOnly);
	out1.write(QJsonDocument(MLevelInfo::toJson(reinterpret_cast<MLevelInfo*>(this->info))).toBinaryData());
	out1.flush();
	out1.close();
}
void MLevel::generateWorld() {
 for(int x = -4 ; x < 4 ; x++)
	 for(int z = -4 ; z < 4 ; z++)
		 addNewChunk(IChunkPos(x, 0, z));
}
void MLevel::reAllocate(IWorldRender *ren) {
	for(IChunk* c : *this->chunkList){
		c->setGlList(ren->getFreeList());
	 c->onReAlloc();
 }
}
bool MLevel::isBlock(IVec3i p) {
	IChunkPos c(
		p.x/IChunk::size,
		p.y/IChunk::size,
		p.z/IChunk::size
	);

	if(chunkList->contains(c)){
		return chunkList->value(c)->getBlock(p.toBlockPos()) != nullptr;
	}
	return false;
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
void MLevel::addNewChunk(IChunkPos c) { this->chunkList->insert(c, new MChunk(this->generator, c));}
//MLevel

//MLevelManager
void loadLevelC(ILevel* l){
	l->load();
}
void genLevelC(ILevel* l){
 l->generateWorld();
}
MLevelManager::MLevelManager(MCoreMods* m) {
	this->loader = m;
	this->list = new QList<ILevelInfo*>;

	// Load list with exist levels
	foreach(QFileInfo i, QDir("saves").entryInfoList( QDir::Dirs | QDir::NoDotAndDotDot)){
		QFile file("saves/" + i.fileName() + "/level.dat");
		file.open(QIODevice::ReadOnly);

	 list->push_back(
		 MLevelInfo::fromJson(
			 QJsonDocument::fromBinaryData(
				 file.readAll()
			 ).object()
		 )
	 );
	}
}
QList<ILevelInfo*>* MLevelManager::getList() {	return this->list;}
ILevel* MLevelManager::getCurrentLevel() {	return this->level;}
ILevelInfo* MLevelManager::getCurrentLevelInfo() {	return this->current;}

void MLevelManager::createLevel(ILevelInfo* i) {
 this->current = i;
 this->level = new MLevel(this->current);
	QtConcurrent::run(this->loader->queue, genLevelC, this->level);
}
void MLevelManager::loadLevel(ILevelInfo *i) {
 this->current = i;
	this->level = new MLevel(this->current);
	QtConcurrent::run(this->loader->queue, loadLevelC, this->level);
}
void MLevelManager::exitLevel(ILevelInfo* i) {
 this->level->save();
}
void MLevelManager::removeLevel(ILevelInfo* i) {

}
