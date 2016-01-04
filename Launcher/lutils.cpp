#include "Launcher/lutils.h"

//Logs
QString getLevelName(GLogLevel lv){
	switch(lv){
	case GLogLevel::ERR  : return "[E]";
	case GLogLevel::WARN : return "[W]";
	case GLogLevel::INFO : return "[I]";
	case GLogLevel::DEBUG: return "[D]";
	case GLogLevel::FINE : return "[F]";
	case GLogLevel::FFINE: return "[FF]";
	case GLogLevel::ALL  : return "[A]";
		//	case GLogLevel::ERR  : return "[ERROR]";
		//	case GLogLevel::WARN : return "[WARNING]";
		//	case GLogLevel::INFO : return "[INFO]";
		//	case GLogLevel::DEBUG: return "[DEBUG]";
		//	case GLogLevel::FINE : return "[FINE]";
	}
}
LLogE::LLogE(GLogLevel lvl,QDateTime dt, QString cls, QString mss):lv(lvl), d(dt), cl(cls), ms(mss), engine(false){}
LLogE::LLogE(QString s){
	QStringList lst = s.split("^");
	t = lst.takeFirst();
	QString level = lst.takeFirst();
	if (level == "[E]"){ lv = GLogLevel::ERR  ;
	}else if (level == "[W]"){ lv = GLogLevel::WARN ;
	}else if (level == "[I]"){ lv = GLogLevel::INFO ;
	}else if (level == "[D]"){ lv = GLogLevel::DEBUG;
	}else if (level == "[F]"){ lv = GLogLevel::FINE ;
	}else if (level == "[FF]"){lv = GLogLevel::FFINE ;
	}else if (level == "[A]"){ lv = GLogLevel::ALL ;
	}else{

	}
 cl = parseQtFunc(lst.takeFirst());
	ms = lst.takeFirst();
	engine = true;
}
QString LLogE::parseQtFunc(QString s) {
	QString	r = s;
	r = r.replace(" void", "");
	r = r.replace("void", "");
	r = r.replace("  ", " ");
	r = QStringRef(&r, r.indexOf(' ') + 1, r.length() - r.indexOf(' ')).toString().insert(1, '-');
	if(NO_DEBUG)	r = QStringRef(&r, 0, r.indexOf(':')).toString();
	return r;
}
QString LLogE::toString(){
	QString r = "<div ";

	switch(lv){
		case GLogLevel::ERR  : r += "style=\"color:red"; break;
		case GLogLevel::WARN : r += "style=\"color:#ff9c00"; break;
		case GLogLevel::INFO : r += "style=\"color:blue"; break;
		case GLogLevel::DEBUG: r += "style=\"color:black"; break;
		case GLogLevel::FINE : r += "style=\"color:gray"; break;
		case GLogLevel::FFINE: r += "style=\"color:gray"; break;
		case GLogLevel::ALL  : r += "style=\"color:gray"; break;
	}

	r.append("\">[");
	r.append(engine ? t : d.toString("HH:mm:ss"));
	//r.append(engine ? t : d.toString("HH:mm:ss dd.MM.yyyy"));
	r.append("]" + getLevelName(lv));
	r.append("["+cl+"]");
	r.append(": "+ms);

	r.append("</div>");
	return r;
}
//Logs

//ModModel
GModLoaderSelect::GModLoaderSelect(QMap<QString, QString> &m, QObject *pobj):QAbstractTableModel(pobj), mp(m){
	this->setHeaderData(0, Qt::Horizontal, "Name");
	this->setHeaderData(1, Qt::Horizontal, "File");
}
QVariant GModLoaderSelect::data(const QModelIndex &index, int nRole) const{
	if (!index.isValid()) {
		return QVariant(); }
	QString str = QString("%1,%2").arg(index.row() + 1).arg(index.column() + 1);
	return (nRole == Qt::DisplayRole || nRole == Qt::EditRole)  ?
				(index.column()==1 ?  mp[mp.keys()[index.row()]] : mp.keys()[index.row()] )
			: QVariant();
	}
	Qt::ItemFlags GModLoaderSelect::flags(const QModelIndex &index) const{
	return QAbstractTableModel::flags(index);
}
int GModLoaderSelect::rowCount(const QModelIndex&) const     {
	return mp.keys().size();
}
int GModLoaderSelect::columnCount(const QModelIndex&) const     {
	return 2;
}
//ModModel

//LSettingsModel
LSettingsModel::LSettingsModel(QString c, QMap<QString, QJsonObject> &m, QObject *pobj):QAbstractTableModel(pobj), cat(c), mp(m){
	foreach(QString s, mp[cat].keys()){if(s != "name") ind << s;}
	this->setHeaderData(0, Qt::Horizontal, "Key");
	this->setHeaderData(1, Qt::Horizontal, "Value");
}
QVariant LSettingsModel::data(const QModelIndex &index, int nRole) const{
	if (!index.isValid()) {
		return QVariant(); }
	QString str = QString("%1,%2").arg(index.row() + 1).arg(index.column() + 1);
	return (nRole == Qt::DisplayRole || nRole == Qt::EditRole)  ?
				(index.column()==1 ?  mp[cat][ind[index.row()]].toString() : ind[index.row()] )
			: QVariant();
	}
	bool LSettingsModel::setData(const QModelIndex &index, const QVariant &value, int nRole){
	if (index.isValid() && nRole == Qt::EditRole) {
	//	if(index.column() == 0){
	//	QString old = ind[index.row()];
	//	mp[cat][value.toString()] = mp[cat][old];
	//	mp[cat].remove(old);
	//}else{
	mp[cat][ind[index.row()]] = value.toString();
	//}
	emit dataChanged(index, index);
	return true;
}
return false;
}
Qt::ItemFlags LSettingsModel::flags(const QModelIndex &index) const{
	Qt::ItemFlags flags = QAbstractTableModel::flags(index);
	return (index.isValid() && index.column() == 1) ? (flags | Qt::ItemIsEditable) : flags;
}
int LSettingsModel::rowCount(const QModelIndex&) const     {
	return ind.size();
}
int LSettingsModel::columnCount(const QModelIndex&) const     {
	return 2;
}
//LSettingsModel

//ListModel
LListModel::LListModel(const QJsonArray &o, QObject *pobj):QAbstractListModel(pobj),obj(o){}
QVariant LListModel::data(const QModelIndex &index, int nRole) const{
	if (!index.isValid()){return QVariant();}
	return (nRole == Qt::DisplayRole || nRole == Qt::EditRole)
			? obj.at(index.row()).toString()
			: QVariant();
}
bool LListModel::setData(const QModelIndex &index, const QVariant &value, int nRole){
	if (index.isValid() && nRole == Qt::EditRole) {
		obj.replace(index.row(), value.toString());
		emit dataChanged(index, index);
		return true;
	}
	return false;
}
int LListModel::rowCount(const QModelIndex&) const{
	return obj.size();
}
QVariant LListModel::headerData(int nSection, Qt::Orientation orientation, int nRole) const{
	if (nRole != Qt::DisplayRole) {return QVariant();}
	return (orientation == Qt::Horizontal) ? QString("Wrong_Model")
																																								: QString::number(nSection);
}
Qt::ItemFlags LListModel::flags(const QModelIndex &index) const{
	Qt::ItemFlags flags = QAbstractListModel::flags(index);
	return index.isValid() ? (flags | Qt::ItemIsEditable): flags;
}
void LListModel::add(QString k){
	obj << k;
}
void LListModel::del(QListView* i){
	QModelIndexList l = i->selectionModel()->selectedRows();

	foreach(const QModelIndex &index, l){
		QString s = index.data(Qt::DisplayRole ).toString();
			int j = 0;
		foreach(QJsonValue v, obj){
			if(s == v.toString()){
				obj.removeAt(j);
			}
					j++;
		}
	}
}
//ListModel

//TableModel
LTableModel::LTableModel(QJsonObject& o, QObject *pobj):QAbstractTableModel(pobj), obj(o){
	this->setHeaderData(0, Qt::Horizontal, "Name");
	this->setHeaderData(1, Qt::Horizontal, "Path");
}
QVariant LTableModel::data(const QModelIndex &index, int nRole) const{
	if (!index.isValid()) {return QVariant(); }
	return (nRole == Qt::DisplayRole || nRole == Qt::EditRole)  ?
				(index.column()==1 ?  obj[obj.keys()[index.row()]].toString() : obj.keys()[index.row()] )
			: QVariant();
	}
	bool LTableModel::setData(const QModelIndex &index, const QVariant &value, int nRole){
	if (index.isValid() && nRole == Qt::EditRole) {
	if(index.column() == 0){
	QString old = obj.keys()[index.row()];
	obj[value.toString()] = obj[old];
	obj.remove(old);
}else{
obj[obj.keys()[index.row()]] = value.toString();
}
emit dataChanged(index, index);
return true;
}
return false;
}
Qt::ItemFlags LTableModel::flags(const QModelIndex &index) const{
	Qt::ItemFlags flags = QAbstractTableModel::flags(index);
	return (index.isValid()) ? (flags | Qt::ItemIsEditable) : flags;
}
void LTableModel::add(QString k, QString v){
	obj[k] = v;
}
void LTableModel::del(QString k){
	obj.remove(k);
}
int LTableModel::rowCount(const QModelIndex&) const{
	return obj.size();
}
int LTableModel::columnCount(const QModelIndex&) const{
	return 2;
}
//TableModel

//MLocalServer
MLocalServer::MLocalServer(LLogWidget* l){
	clients = new QVector<QLocalSocket*>();
	log = l;
	blockSize = 0;

	server = new QLocalServer(this);
	if (!server->listen("GameLogServer")) {
		qDebug() << "Construction failed "+server->errorString();
		return;
	}

	connect(server, SIGNAL(newConnection()), this, SLOT(newConnection()));

	QTimer *timer = new QTimer(this);
	connect(timer, SIGNAL(timeout()), this, SLOT(readyRead()));
	timer->start(50);
}
void MLocalServer::addLog(QString s){
	if(s.indexOf("#Launcher") == 0){
		if(s.indexOf("#Launcher#Disconnect") == 0){
			clients->clear();
		}
	}else{
		log->addL(LLogE(s));
	}
}
void MLocalServer::newConnection(){
	QLocalSocket* client = server->nextPendingConnection();
//	connect(client, SIGNAL(disconnected()),	client, SLOT(deleteLater()));
	connect(client, SIGNAL(readyRead()), this, SLOT(readyRead()));
	clients->append(client);
	log->addL(GLogLevel::DEBUG, "L-MLocalServer", "Engine connected");
}
void MLocalServer::readyRead(){
	foreach(QLocalSocket* client , *clients){
		if(client->isOpen()){
			QDataStream in(client);
			in.setVersion(QDataStream::Qt_5_4);

			if (in.atEnd())
				return;

			if (blockSize == 0) {
				if (client->bytesAvailable() < (int)sizeof(quint16))
					return;
				in >> blockSize;
			}

			QString curr;
			in >> curr;

			if (curr != lastMsg) {
				addLog(curr);
				blockSize = 0;
			}
		}
	}
}
//MLocalServer
//Json
void createJson(){
	QFile f("cmod-1.cfg");
	if (!f.open(QIODevice::WriteOnly)) {return;}
	QJsonObject obj;

	obj["name"] = "Test core mod - 1";
	obj["type"] = "CoreMod";
	obj["desc"] = "Description";
	obj["devl"] = "IlzSoft company";
	obj["site"] = "github.com";
	obj["depend"] = QJsonArray();
	obj["res"] = QJsonArray();
	obj["version"] = "1.0";
	obj["revision"] = "1.0";

	QJsonDocument doc(obj);
	f.write(qCompress(doc.toBinaryData(),5));
	f.flush();
	f.close();
}
QJsonObject loadJson(QFile file){
	file.open(QIODevice::ReadOnly);
	QJsonDocument loadDoc(QJsonDocument::fromBinaryData(qUncompress(file.readAll())));
	return loadDoc.object();
}
QJsonArray loadJsonA(QFile file){
	file.open(QIODevice::ReadOnly);
	QJsonDocument loadDoc(QJsonDocument::fromBinaryData(qUncompress(file.readAll())));
	return loadDoc.array();
}
QJsonObject loadJson(QString file){
	QFile loadFile(file);
	qDebug() << "loading " << file;
	loadFile.open(QIODevice::ReadOnly);

	QJsonDocument loadDoc(QJsonDocument::fromBinaryData(qUncompress(loadFile.readAll())));
	return loadDoc.object();
}
QJsonArray loadJsonA(QString file){
	QFile loadFile(file);
	qDebug() << "loading " << file;
	loadFile.open(QIODevice::ReadOnly);

	QJsonDocument loadDoc(QJsonDocument::fromBinaryData(qUncompress(loadFile.readAll())));
	return loadDoc.array();
}
void saveJson(QJsonObject o, QString file){
	QFile f(file);
	if (!f.open(QIODevice::WriteOnly)) {return;}

	QJsonDocument doc(o);
	f.write(qCompress(doc.toBinaryData(),5));
	f.flush();
	f.close();
}
void saveJsonA(QJsonArray o, QString file){
	QFile f(file);
	if (!f.open(QIODevice::WriteOnly)) {return;}

	QJsonDocument doc(o);
	f.write(qCompress(doc.toBinaryData(),5));
	f.flush();
	f.close();
}
//Json

QStringList getPluginFilter(){
	QStringList r;
	//#ifdef Q_OS_WIN
	r << "*.dll";
	//#endif

	return r;
}


//MModsList
MModsList::MModsList(LMainWindow *l):loader(l){
	this->list = new QJsonArray;
	this->lst = QJsonArray();
}
void MModsList::update(){
	QDir mods("mods/mods");
			foreach(QFileInfo f, mods.entryInfoList(QDir::Dirs | QDir::NoDotAndDotDot)){
			if(f.fileName() != "." && f.fileName() != ".."){
				loader->w_log->addL(GLogLevel::DEBUG, "ModsWidget", "parsing "+f.filePath());
				addToList(loadJson(QDir("mods/mods/"+f.fileName()).filePath("pack.dat")));
			}
		}

}
void MModsList::fillList(){
	lst = QJsonArray();
			foreach(QJsonValue o, *list){
			if(o.toObject()["enabled"].toBool() && !lst.contains(o.toObject()["name"].toString())){
				lst << o.toObject()["name"].toString();
			}
		}
}
void MModsList::addToList(QJsonObject o){
	if(contains(o["name"].toString())){
		loader->w_log->addL(GLogLevel::DEBUG, "ModsWidget", o["name"].toString()+" has already added, ignoring ");
	}else{
		loader->w_log->addL(GLogLevel::DEBUG, "ModsWidget", "found new mod, adding "+o["name"].toString());
		QJsonObject t;
		t["name"] = o["name"];
		t["desc"] = o["desc"];
		t["enabled"] = true;
		*list << t;
		this->lst << o["name"].toString();
	}
}
bool MModsList::contains(QString s){
			foreach(QJsonValue v, *list){
			if( (v.toObject())["name"] == s ) return true;
		}
	return false;
}
void MModsList::disable(QString n){
			foreach(QJsonValue v, *list){
			if(v.toObject()["name"] == n){
				v.toObject()["enabled"] = false;
			}
		}
}
void MModsList::addNew(){
	QString file = QFileDialog::getOpenFileName(loader->dev->w_mod, tr("Open File"),"/home",qPrintable("Mod (*"+ME_SAVE+")"));
	QString ffile = QStringRef(&file, file.lastIndexOf("/")+1, file.indexOf(".zip")).toString();
	QZipReader z(file);
	loader->w_log->addL(GLogLevel::DEBUG, "BaseModLoader", "unzipping "+file + " to " + ffile);
	//z.extractAll("mods/");
}
void MModsList::load(){
	QFile f("mods/mods.dat");
	if(f.exists()){
		list = new QJsonArray(loadJsonA(f.fileName()));
	}else{
		loader->w_log->addL(GLogLevel::DEBUG, "ModsWidget", "file mods/mods.dat not exist");
		list = new QJsonArray();
	}
	update();
	fillList();
}
void MModsList::save(){
			foreach(QJsonValue e, *list){
			QJsonObject o = e.toObject();
			o["enabled"] = lst.contains(o["name"].toString());
		}
	saveJsonA(*list, "mods/mods.dat");
}
void MModsList::reload(){
	this->list = new QJsonArray();
	update();
}
//!MModsList
