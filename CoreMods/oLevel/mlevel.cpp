#include <mlevel.h>
#include <QtConcurrent/QtConcurrent>


// MLevelInfo
MLevelInfo::MLevelInfo(){this->custom = new QJsonObject;}

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
 for(QString k : obj.keys()){
			if((k.compare("name") != 0)
			 ||(k.compare("dir")  != 0)
				)
				info->custom->insert(k, obj.value(k));
		}
	return info;
}

void MLevelInfo::addCustom(QJsonObject object) {
		for(QString s : object.keys()){
			this->custom->insert(s, object.value(s));
		}
}
// MLevelInfo

// MLevel
MLevel::MLevel(ILevelInfo* info) {
	this->info = info;
	this->info->setDir("saves/" + info->getName() + "/");
	QDir().mkpath(this->info->getDir());

	this->chunkList = new QMap<IAChunkPos, IChunk*>;
	this->generator = new MWorldGenerator;
}

void MLevel::load() {
	QFile file(info->getDir()+"chunks.dat");
	file.open(QIODevice::ReadOnly);
 QByteArray arr = qUncompress(file.readAll());
	QDataStream in(&arr, QIODevice::ReadOnly);
	QJsonObject obj = info->getFromCustom("chunks").toObject();
	QJsonArray ids = info->getFromCustom("chunkIds").toArray();

	for(QJsonValue v : ids) loadChunk(v, obj, in);

}

void MLevel::loadChunk(QJsonValue v, QJsonObject obj, QDataStream &in) {
	int size = 262144;
	char* ch;

	ch = new char[size];
	in.skipRawData(4);
	in.readRawData(ch, size);

	IAChunkPos pos(
		quint16(v.toObject().value("c").toDouble()),
		qint32(v.toObject().value("rX").toDouble()),
		qint32(v.toObject().value("rY").toDouble()),
		qint32(v.toObject().value("rZ").toDouble())
	);

	chunkList->insert(pos, new MChunk(
		QByteArray(ch, size),
		obj["chunk" + QString::number(pos.x()) + QString::number(pos.y()) + QString::number(pos.z())].toObject(),
		pos
	));

	delete[] ch;

}

void MLevel::save() {
	QJsonArray ids;
	QJsonObject obj;
	QByteArray arr;
	QDataStream stream(&arr, QIODevice::WriteOnly);

		for(IAChunkPos p : this->chunkList->keys()) {
			QJsonObject o;
			o.insert("c", p.c());
			o.insert("rX", p.rX());
			o.insert("rY", p.rY());
			o.insert("rZ", p.rZ());
			ids.append(o);
		}
	info->addToCustom("chunkIds", ids);

		for(IChunk* p : this->chunkList->values())	p->write(stream, obj);
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
 for(int x = -16 ; x < 16 ; x++)
	 for(int z = -16 ; z < 16 ; z++)
		 addNewChunk(IAChunkPos(x, 0, z));
}

void MLevel::reAllocate(IWorldRender *ren) {
	for(IChunk* c : *this->chunkList){
		c->setGlList(ren->getFreeList());
	 c->onReAlloc();
 }
	ren->setChunks(chunkList);

}

bool MLevel::isBlock(IVec3i p) {
	IAChunkPos c(
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

IChunk * MLevel::getChunk(IAChunkPos pos) {
 if(this->chunkList->contains(pos)){
	 return this->chunkList->value(pos);
 }else{
	 return new MChunk();
 }
}

void MLevel::addNewChunk(IAChunkPos c) { this->chunkList->insert(c, new MChunk(this->generator, c));}
// MLevel

// MLevelManager
void loadLevelC(ILevel* l){
	l->load();
}
void genLevelC(ILevel* l){
 l->generateWorld();
}
MLevelManager::MLevelManager() {
	this->list = new QList<ILevelInfo*>;
	this->queue = varG(QThreadPool*, "eThreadQueue");

	// Load list with exist levels
	for(QFileInfo i : QDir("saves").entryInfoList( QDir::Dirs | QDir::NoDotAndDotDot)){
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

void MLevelManager::createLevel(ILevelInfo* i) {
 this->current = i;
 this->level = new MLevel(this->current);
	QtConcurrent::run(queue, genLevelC, this->level);
}

void MLevelManager::loadLevel(ILevelInfo *i) {
 this->current = i;
	this->level = new MLevel(this->current);
	QtConcurrent::run(queue, loadLevelC, this->level);
}

void MLevelManager::loadLevel(QString name) {
	MLevelInfo *i = new MLevelInfo;
	i->setName(name);

	this->current = i;
	this->level = new MLevel(this->current);
	QtConcurrent::run(queue, loadLevelC, this->level);
}

void MLevelManager::exitLevel(ILevelInfo* i) {
 this->level->save();
}

void MLevelManager::removeLevel(ILevelInfo* i) {

}
// MLevelManager



