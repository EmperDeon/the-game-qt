#include <eutils.h>

// Logger
QString getLevelName(ILogLevel lv){
	switch(lv){
		case ILogLevel::ERR  : return "[E]";
		case ILogLevel::WARN : return "[W]";
		case ILogLevel::INFO : return "[I]";
		case ILogLevel::DEBUG: return "[D]";
		case ILogLevel::FINE : return "[F]";
		case ILogLevel::FFINE: return "[FF]";
		case ILogLevel::ALL  : return "[A]";
		case ILogLevel::QT   : return "[QT]";
	}
}

void ELogger::connected(){	conn = true;}

void ELogger::disc(){	conn = false;}

ELogger::ELogger(){
	socket = new QLocalSocket();
	connect(socket, SIGNAL(connected()), this, SLOT(connected()));
	connect(socket, SIGNAL(disconnected()), this, SLOT(disc()));
	conn = false;
	socket->connectToServer(ESERVER_NAME);
}

void ELogger:: log(ILogLevel lv, QString cl, QString ms){
	QString s = QDateTime::currentDateTime().toString(ELOG_DATE_FORMAT) + "^";
	s += getLevelName(lv) +  "^";
	s += cl + "^";
	s += ms;

	sendM(s);
}

void ELogger::sendM(QString s) {
	if (!conn) {	socket->connectToServer(ESERVER_NAME);	}

	QByteArray block;
	QDataStream out(&block, QIODevice::WriteOnly);
	out.setVersion(QDataStream::Qt_5_4);

	out << (quint16) 0;
	out << s;
	out.device()->seek(0);
	out << (quint16) (block.size() - sizeof(quint16));

	socket->write(block);
	socket->flush();
}

ILogger*IV_LOGGER;
// Logger


// Settings
ESettings::ESettings(QString f):map(),file(f){}

ESettings::~ESettings(){}

QJsonObject &ESettings::operator[] (QString k){
	logFF("Get " + k);
	if (!map.contains(k)){
		logW("This settings does not contain that category: "+k);
		addNewCategory(k);
	}
	return map[k];
}

QJsonObject &ESettings::get(QString n){
	logFF("Get " + n);
	if (!map.contains(n)){
		logW("This settings does not contain that category: "+n);
		addNewCategory(n);
	}
	return map[n];
}

void ESettings::addNewCategory(QString n){
	logFF("Adding new category " + n);
	QJsonObject object;
	object["name"]=n;
	this->map[n] = object;
}

void ESettings::save(){
	saveTo(file);
}

void ESettings::load(){
	loadFrom(file);
}

void ESettings::loadFrom(QString f){
	QFile loadFile(f);

	if (!loadFile.open(QIODevice::ReadOnly)) {
		logE("Couldn't open settings file. (" + f + ")");
		return;
	}

	//	QJsonDocument loadDoc(QJsonDocument::fromBinaryData(loadFile.readAll()));
	QJsonDocument loadDoc(QJsonDocument::fromBinaryData(qUncompress(loadFile.readAll())));
	loadFile.close();
	QJsonArray obj = loadDoc.array();

	QJsonObject t;
	for(QJsonValue e : obj){
		t = e.toObject();
		this->map.insert(t["name"].toString(), QJsonObject(t));
	}
	logF("Settings loaded");
}

void ESettings::saveTo(QString f){
	QFile saveFile(f);

	if (!saveFile.open(QIODevice::WriteOnly)) {
		logE("Couldn't open settings file. (" + f + ")");
		return;
	}

	QJsonArray obj;
	for(QJsonObject e : map) {
		obj << e;
	}

	QJsonDocument doc(obj);
	//saveFile.write(doc.toBinaryData());
	saveFile.write(qCompress(doc.toBinaryData(), 1));
	saveFile.flush();
	saveFile.close();
	logF("Settings saved");
}
ISettings*IV_SETT;


ESettCont::ESettCont(){map = new QMap<QString, ISettings*>;}

ISettings *ESettCont::getSettings(QString k) {
	if(!map->contains(k)){
		map->insert(k, new ESettings(k));
	}
	return map->value(k);
}

ISettCont*IV_SETC;
// Settings


// Vars
EVars::EVars(){
	map = new QMap<QString, void*>;
	loader = nullptr;
	owlist = new QStringList;
}

bool EVars::contains(QString name){
	return map->contains(name);
}

bool EVars::contains(QStringList names) {
	bool c = true;
	for(QString n : names ){
		c = c && map->contains(n);
	}
	return c;
}

void*EVars::get(QString name){
	logFF("Get " + name);
	if(!contains(name))
		set(loader->get(name), name);
	return (*map)[name];
}

void *EVars::getN(QString name) {
	return loader->getN(name);
}

void *EVars::getN(QString name, QJsonObject arg) {
	return loader->getN(name, arg);
}

IVarsSelect *EVars::getLoader() {
	return loader;
}

void EVars::set(void *o, QString name){
	logFF("Set " + name);
	if(!map->contains(name)){
		map->insert(name, o);
	}else{
		if(owlist->contains(name)){
			map->insert(name, o);
		}
	}
}

void EVars::setOverwriteList(QStringList names) {
	this->owlist = new QStringList(names);
}

void EVars::setVarsLoader(IVarsSelect *l) {
 this->loader = l;
}

IVars*IV_VARS;
// Vars


// Dirs
EDirs::EDirs() {
 this->dirs = new QMap<QString, QString>;
}

void EDirs::addDir(QString k, QString v) {
 if(!v.endsWith("/"))
	 v += '/';
	this->dirs->insert(k, v);
}

QDir *EDirs::getDir(QString k) {	return new QDir(dirs->value(k));}

QFile *EDirs::getFile(QString k, QString f) {	return new QFile(dirs->value(k) + f);}

QString EDirs::getSDir(QString k) {	return dirs->value(k); }

QString EDirs::getSFile(QString k, QString f) {	return dirs->value(k) + f; }

IDirs*IV_DIRS;
// Dirs


