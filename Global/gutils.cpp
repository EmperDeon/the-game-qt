#include <Global/gutils.h>
#undef CLASS_NAME

#define CLASS_NAME "Logger"

QString getLevelName(GLogLevel lv){
	switch(lv){
		case GLogLevel::ERR  : return "[E]";
		case GLogLevel::WARN : return "[W]";
		case GLogLevel::INFO : return "[I]";
		case GLogLevel::DEBUG: return "[D]";
		case GLogLevel::FINE : return "[F]";
		case GLogLevel::FFINE: return "[F]";
		case GLogLevel::ALL  : return "[A]";
	}
	return "";
}
void GLogger::connected(){
	conn = true;
}
void GLogger::disc(){
	conn = false;
}
GLogger::GLogger():QObject(){
	socket = new QLocalSocket();
	connect(socket, SIGNAL(connected()), this, SLOT(connected()));
	connect(socket, SIGNAL(disconnected()), this, SLOT(disc()));
	conn = false;
	socket->connectToServer("GameLogServer");
}
void GLogger:: log(GLogLevel lv, QString cl, QString ms){
	//QString s = QDateTime::currentDateTime().toString("HH:mm:ss dd.MM.yyyy") + "^";
	QString s = QDateTime::currentDateTime().toString("HH:mm:ss") + "^";
	s += getLevelName(lv) + "^E-";
	s += cl + "^";
	s += ms;

	sendM(s);
}
void GLogger::sendM(QString s){
	if(!conn){
		socket->connectToServer("GameLogServer");
	}

	QByteArray block;
	QDataStream out(&block, QIODevice::WriteOnly);
	out.setVersion(QDataStream::Qt_5_4);

	out << (quint16)0;
	out << s;
	out.device()->seek(0);
	out << (quint16)(block.size() - sizeof(quint16));

	socket->write(block);
	socket->flush();
}
void GLogger::connec(){

}

GLogger GV_LOGGER;

#undef CLASS_NAME
#define CLASS_NAME "Settings"

GSettings::GSettings(QString f):map(),file(f){}
GSettings::~GSettings(){}

QJsonObject& GSettings::operator[] (QString k){
	if (!map.contains(k)){
		logW("This settings does not contain that category: "+k);
		addNewCategory(k);
	}
	return map[k];
}
QJsonObject &GSettings::get(QString n){
	if (!map.contains(n)){
		logW("This settings does not contain that category: "+n);
		addNewCategory(n);
	}
	return map[n];
}
void GSettings::addNewCategory(QString n){
	QJsonObject object;
	object["name"]=n;
	this->map[n] = object;
}
void GSettings::save(){
	saveTo(file);
}
void GSettings::load(){
	loadFrom(file);
}
void GSettings::loadFrom(QString f){
	QFile loadFile(f);

	if (!loadFile.open(QIODevice::ReadOnly)) {
		logE("Couldn't open settings file. ("+f+")");
		return;
	}

	//	QJsonDocument loadDoc(QJsonDocument::fromBinaryData(loadFile.readAll()));
	QJsonDocument loadDoc(QJsonDocument::fromBinaryData(qUncompress(loadFile.readAll())));
	QJsonArray obj = loadDoc.array();
	QJsonObject t;
	foreach(QJsonValue e , obj){
		t = e.toObject();
		this->map[t["name"].toString()] = QJsonObject(t);
	}
}
void GSettings::saveTo(QString f){
	QFile saveFile(f);

	if (!saveFile.open(QIODevice::WriteOnly)) {
		logE("Couldn't open settings file. ("+f+")");
		return;
	}

	QJsonArray obj;

	foreach (QJsonObject e, map) {
		obj << e;
	}

	QJsonDocument doc(obj);
	//saveFile.write(doc.toBinaryData());
	saveFile.write(qCompress(doc.toBinaryData(),5));
}

GSettings GV_SETTINGS("settings.dat");

#undef CLASS_NAME
#define CLASS_NAME "GVars"


GVars::GVars(){
	map = new QMap<QString, QObject*>;
}
bool GVars::contains(QString name){
	return map->contains(name);
}
QObject *GVars::get(QString name){
	return (*map)[name];
}
void GVars::set(QObject *o, QString n){
	(*map)[n] = o;
}

GVars GV_VARS;

#undef CLASS_NAME
#define CLASS_NAME "Not_Defined"
