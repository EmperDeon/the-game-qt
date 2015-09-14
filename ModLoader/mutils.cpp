#include "mutils.h"

// Json
QJsonObject loadJson(QString file){
	QFile loadFile(file);
	qDebug() << "loading " << file;
	loadFile.open(QIODevice::ReadOnly);

	QJsonDocument loadDoc(QJsonDocument::fromBinaryData(qUncompress(loadFile.readAll())));
	return loadDoc.object();
}
void saveJson(QJsonObject o, QString file){
	QFile f(file);
	if (!f.open(QIODevice::WriteOnly)) {return;}

	QJsonDocument doc(o);
	f.write(qCompress(doc.toBinaryData(),5));
	f.flush();
	f.close();
}

void LLogWidget::addL(GLogLevel lv, QString cl, QString m){
	GLogE e = GLogE(lv, QDateTime::currentDateTime(), "BML-"+cl, m );
	if(lv <= curr){
		last += e.toString();
		w_edit->setHtml(last);
	}
	list->append(e);
	qDebug() << e.toString();
}
QString getLevelName(GLogLevel lv){
	switch(lv){
	case GLogLevel::ERR  : return "[E]";
	case GLogLevel::WARN : return "[W]";
	case GLogLevel::INFO : return "[I]";
	case GLogLevel::DEBUG: return "[D]";
	case GLogLevel::FINE : return "[F]";
	case GLogLevel::FFINE: return "[F]";
	case GLogLevel::ALL  : return "[A]";
		//	case GLogLevel::ERR  : return "[ERROR]";
		//	case GLogLevel::WARN : return "[WARNING]";
		//	case GLogLevel::INFO : return "[INFO]";
		//	case GLogLevel::DEBUG: return "[DEBUG]";
		//	case GLogLevel::FINE : return "[FINE]";
	}
	return "";
}
GLogE::GLogE(GLogLevel lvl,QDateTime dt, QString cls, QString mss):lv(lvl), d(dt), cl(cls), ms(mss){

}
QString GLogE::toString(){
	QString t = "<div ";

	switch(lv){
	case GLogLevel::ERR  : t += "style=\"color:red"; break;
	case GLogLevel::WARN : t += "style=\"color:#ff9c00"; break;
	case GLogLevel::INFO : t += "style=\"color:blue"; break;
	case GLogLevel::DEBUG: t += "style=\"color:black"; break;
	case GLogLevel::FINE : t += "style=\"color:gray"; break;
	case GLogLevel::FFINE: t += "style=\"color:gray"; break;
	case GLogLevel::ALL  : t += "style=\"color:gray"; break;
	}

	//t += "\">[" + d.toString("HH:mm:ss dd.MM.yyyy") + "]";
	t += "\">[" + d.toString("HH:mm:ss") + "]";
	t.append(getLevelName(lv));
	t.append("["+cl+"]");
	t.append(": "+ms);

	t.append("</div>");
	return t;
}
//

//ListModel
MListModel::MListModel(const QJsonArray &o, QObject *pobj):QAbstractListModel(pobj),obj(o){}
QVariant MListModel::data(const QModelIndex &index, int nRole) const{
	if (!index.isValid()){return QVariant();}
	return (nRole == Qt::DisplayRole || nRole == Qt::EditRole)
			? obj.at(index.row()).toString()
			: QVariant();
}
bool MListModel::setData(const QModelIndex &index, const QVariant &value, int nRole){
	if (index.isValid() && nRole == Qt::EditRole) {
		obj.replace(index.row(), value.toString());
		emit dataChanged(index, index);
		return true;
	}
	return false;
}
int MListModel::rowCount(const QModelIndex&) const{
	return obj.size();
}
QVariant MListModel::headerData(int nSection, Qt::Orientation orientation, int nRole) const{
	if (nRole != Qt::DisplayRole) {return QVariant();}
	return (orientation == Qt::Horizontal) ? QString("Wrong_Model")
																																								: QString::number(nSection);
}
Qt::ItemFlags MListModel::flags(const QModelIndex &index) const{
	Qt::ItemFlags flags = QAbstractListModel::flags(index);
	return index.isValid() ? (flags | Qt::ItemIsEditable): flags;
}
void MListModel::add(QString k){
	obj << k;
	emit dataChanged(index(0,0), index(obj.size(), 0));
}
void MListModel::del(QListView* i){
	QModelIndexList l = i->selectionModel()->selectedRows();

	foreach(const QModelIndex &index, l){
		QString s = index.data(Qt::DisplayRole ).toString();
		int i = 0;
		foreach(QJsonValue v, obj){
			if(s == v.toString()){
				obj.removeAt(i);
			}
			i++;
		}
	}
	emit dataChanged(index(0,0), index(obj.size(), 0));
}
//ListModel

//TableModel
MTableModel::MTableModel(QJsonObject& o, QObject *pobj):QAbstractTableModel(pobj), obj(o){
	this->setHeaderData(0, Qt::Horizontal, "Name");
	this->setHeaderData(1, Qt::Horizontal, "Path");
}
QVariant MTableModel::data(const QModelIndex &index, int nRole) const{
	if (!index.isValid()) {return QVariant(); }
	return (nRole == Qt::DisplayRole || nRole == Qt::EditRole)  ?
				(index.column()==1 ?  obj[obj.keys()[index.row()]].toString() : obj.keys()[index.row()] )
			: QVariant();
	}
	bool MTableModel::setData(const QModelIndex &index, const QVariant &value, int nRole){
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
Qt::ItemFlags MTableModel::flags(const QModelIndex &index) const{
	Qt::ItemFlags flags = QAbstractTableModel::flags(index);
	return (index.isValid()) ? (flags | Qt::ItemIsEditable) : flags;
}
void MTableModel::add(QString k, QString v){
	obj[k] = v;
	emit dataChanged(index(0,0), index(obj.size(), 1));
}
void MTableModel::del(QString k){
	obj.remove(k);
	emit dataChanged(index(0,0), index(obj.size(), 1));
}
int MTableModel::rowCount(const QModelIndex&) const{
	return obj.size();
}
int MTableModel::columnCount(const QModelIndex&) const{
	return 2;
}
//TableModel

//ListManager
MListManager::MListManager(QJsonArray &o, QString t){
	model = new MListModel  (o);
	list	 = new QListView  ();
	vlay  = new QVBoxLayout();
	hlay  = new QHBoxLayout();
	e_k		 = new QLineEdit  ();
	b_add = new QPushButton("Add");
	b_del = new QPushButton("Delete selected");
	b_ok	 = new QPushButton("Ok");

	hlay->addWidget(e_k);
	hlay->addWidget(b_add);
	hlay->addWidget(b_del);
	vlay->addLayout(hlay);
	vlay->addWidget(list);
	vlay->addWidget(b_ok);
	list->setModel(model);

	connect(b_add, SIGNAL(clicked()), this, SLOT(add()));
	connect(b_del, SIGNAL(clicked()), this, SLOT(del()));
	connect(b_ok,  SIGNAL(clicked()), this, SLOT(hide()));

	this->setLayout(vlay);
	this->setWindowTitle(t);
}
void MListManager::add(){
	this->model->add(e_k->text());
}
void MListManager::del(){
	this->model->del(list);
}
//!ListManager

//TableManager
MTableManager::MTableManager(QJsonObject &o, QString t){
	model = new MTableModel(o);
	table	= new QTableView ();
	vlay  = new QVBoxLayout();
	hlay  = new QHBoxLayout();
	e_k		 = new QLineEdit  ("Key");
	e_v		 = new QLineEdit  ("Value");
	b_add = new QPushButton("Add");
	b_del = new QPushButton("Delete selected");
	b_ok	 = new QPushButton("Ok");

	hlay->addWidget(e_k);
	hlay->addWidget(e_v);
	hlay->addWidget(b_add);
	hlay->addWidget(b_del);
	vlay->addLayout(hlay);
	vlay->addWidget(table);
	vlay->addWidget(b_ok);
	table->setModel(model);

	connect(b_add, SIGNAL(clicked()), this, SLOT(add()));
	connect(b_del, SIGNAL(clicked()), this, SLOT(del()));
	connect(b_ok,  SIGNAL(clicked()), this, SLOT(hide()));

	this->setLayout(vlay);
	this->setWindowTitle(t);
}
void MTableManager::add(){
	this->model->add(e_k->text(), e_v->text());
}
void MTableManager::del(){
	this->model->del(e_k->text());
}
//!TableMananger

//MModsList
MModsList::MModsList(ModLoader *l):loader(l){
	this->list = new QJsonArray;
	this->lst = QJsonArray();
}
void MModsList::update(){
	QDir mods("mods");
	foreach(QFileInfo f, mods.entryInfoList(QDir::Dirs | QDir::NoDotAndDotDot)){
		if(f.fileName() != "." && f.fileName() != ".."){
			loader->w_log->addL(GLogLevel::DEBUG, "ModsWidget", "parsing "+f.filePath());
			addToList(loadJson(QDir("mods/"+f.fileName()).filePath("pack.dat")));
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
	QString file = QFileDialog::getOpenFileName(loader->w_mod, tr("Open File"),"/home",qPrintable("Mod (*"+ME_SAVE+")"));
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
		if(lst.contains(o["name"].toString())){
			o["enabled"] = true;
		}else{
			o["enabled"] = false;
		}
	}
	saveJsonA(*list, "mods/mods.dat");
}
void MModsList::reload(){
	this->list = new QJsonArray();
	update();
}
//!MModsList
