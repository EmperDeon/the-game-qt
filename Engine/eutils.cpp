#include <Engine/eutils.h>

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

ILogger* GV_LOGGER;
// Logger


// Settings
ESettings::ESettings(QString f):map(),file(f){}

ESettings::~ESettings(){}

QJsonObject&ESettings::operator[] (QString k){
	if (!map.contains(k)){
		logW("This settings does not contain that category: "+k);
		addNewCategory(k);
	}
	return map[k];
}

QJsonObject &ESettings::get(QString n){
	if (!map.contains(n)){
		logW("This settings does not contain that category: "+n);
		addNewCategory(n);
	}
	return map[n];
}

void ESettings::addNewCategory(QString n){
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
	QJsonArray obj = loadDoc.array();
	QJsonObject t;
	for(QJsonValue e : obj){
		t = e.toObject();
		this->map[t["name"].toString()] = QJsonObject(t);
	}
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
	saveFile.write(qCompress(doc.toBinaryData(),5));
}
// Settings


// Vars
EVars::EVars(){
	map = new QMap<QString, void*>;
	owlist = new QStringList;
}

bool EVars::contains(QString name){
	return map->contains(name);
}

bool EVars::contains(QStringList l) {
	bool c = true;
	for(QString n : l){
		c = c && map->contains(n);
	}
	return c;
}

void*EVars::get(QString name){
	if(!contains(name))
		logE("No " + name + " in EVars");
	return (*map)[name];
}

void EVars::set(void *o, QString n){
	if(!map->contains(n)){
		(*map)[n] = o;
	}else{
		if(owlist->contains(n)){
			(*map)[n] = o;
		}
	}
}

void EVars::setOverwriteList(QStringList l) {
	this->owlist = new QStringList(l);
}

IVars* GV_VARS;
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

IDirs* GV_DIRS;
// Dirs