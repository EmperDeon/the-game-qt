#include <lparser.h>

// LZips
LZipEntry::LZipEntry(QJsonObject o, QString f){
	name = o["name"].toString();
	desc = o["desc"].toString();
	devl = o["devl"].toString();
	site = o["site"].toString();
	type = o["type"].toString();
	depn = o["depend"].toArray();
	ower = o["owerwr"].toArray();
	ver  = o["version"].toString();
	rev  = o["revision"].toString();
	this->file = f;
}

QString LZipEntry::toString(){
	QString dep, owr;
	for(QJsonValue e : depn){
		dep += e.toString() + "; ";
	}
	for(QJsonValue e : ower) {
		owr += e.toString() + "; ";
	}
	return
		"Name: " + name +
		", Description: " + desc +
		", Developer: " + devl +
		", Site: " + site +
		", Type: " + type +
		", Dependency:[" + dep +
		"], Owerwriting classes:[" + owr +
		"], Version: " + ver +
		", Revision: " + rev;
}

QString LZipErr::toString(){
	return entr.toString() + " : " + err;
}

bool LZipEntry::isValid(){
	return (rev == ParserVer) && (
		(type == "Mod")||
		(type == "CoreMod")||
		(type == "Resource")||
		(type == "Pack"));
}
// LZips


// LParser
LParser::LParser(){
	list = new QList<LZipEntry>;

	err = new QList<LZipErr>;

	coremods = new QStringList;
	mods = new QStringList;
	packs = new QStringList;
	unknown = new QStringList;

	QJsonObject o;
	o["name"] = "NotFound";
	o["type"] = "NotFound";
	o["desc"] = "NotFound";
	o["devl"] = "NotFound";
	o["site"] = "NotFound";
	o["depend"] = QJsonArray();
	o["version"] = "0";
	o["revision"] = "0";
	not_found = LZipEntry(o, "NotFound");

	lLogD("Constructed");
}

//  Adds
void LParser::addE(LZipEntry e, QDir curr){
	if(e.isValid()){
		if(e.type == "Pack"){

			for(QFileInfo f : curr.entryInfoList(QDir::Dirs)){
				LZipEntry t =  LZipEntry(loadJson(QDir("tmp/" + f.fileName()).filePath("archive.dat")), "");
				addE(t,f.dir());
			}

		}else{
			list->append(e);
		}
	}else{
		err->append(LZipErr(e, "Zip is not valid"));
	}
}

void LParser::addToList(LZipEntry e){
	QString type = e.type;
	if(type == "Coremod"){
		*coremods << e.file;
	}else if(type == "Mod"){
		*mods << e.file;
	}else if(type == "ResourcePack"){
		*packs << e.file;
	}else{
		*unknown << e.file;
	}
}
//  Adds


//  Parsing
void LParser::parseZip(){
	unzipDownloads();
	parse();
	check();
	if(err->empty()){
		write();
		clear();
	}else{
		showErr();
	}
}

void LParser::unzipDownloads(){
	QDir down("downloads");
	QDir tmp("");
	tmp.mkdir("tmp");
	tmp.cd("tmp/");

	QFileInfoList downf = down.entryInfoList(QDir::Files);
	for(QFileInfo f : downf){
		lLogD("extracting " + f.filePath());
		QZipReader t("downloads/"+f.fileName());
		tmp.mkdir(f.baseName());
		t.extractAll("tmp/"+f.baseName()+"/");
		down.remove(f.fileName());
	}
}

void LParser::parse(){
	QDir tmp("tmp");
	for(QFileInfo f : tmp.entryInfoList(QDir::Dirs | QDir::NoDotAndDotDot)){
		if(f.fileName() != "." && f.fileName() != ".."){
			lLogD("parsing " + f.filePath());
			LZipEntry t =  LZipEntry(loadJson(QDir("tmp/" + f.fileName()).filePath("pack.dat")), f.fileName());
			addE(t,f.dir());
		}else{
			lLogD("ignoring " + f.filePath());
		}
	}
}

void LParser::check(){
	QStringList names;
	QStringList depen;
	for(LZipEntry e : *list){
		if(!names.contains(e.name)){
			names << e.name;
		}else{
			err->append(LZipErr(e, "Duplicate zip name"));
		}
		if(!e.depn.empty()){
			QString t;
			for(QJsonValue v : e.depn){
				t = v.toString();
				if(!depen.contains(t)){
					depen << t;
				}
			}
		}
		addToList(e);
	}
	for(QString e : depen){
		if(!names.contains(e)){
			err->append(LZipErr(search(e), "Unsatisfied dependency"));
		}
	}

	for(QFileInfo f : QDir("mods/coremods").entryInfoList(QDir::Dirs | QDir::NoDotAndDotDot)) {
		if(!QFile(QDir(f.filePath()).filePath("pack.dat")).exists()) {
			for(QFileInfo f1 : QDir(f.filePath()).entryInfoList(QDir::Files | QDir::NoDotAndDotDot)) {
				(new LModFixer(f1.filePath()))->show();
			}
		}
	}

}
//  Parsing


//  Errors
void LParser::showErr(){
	for(LZipErr e : *err){
		lLogE(e.toString());
	}
}
//  Errors


//  Write
void LParser::write(){
	QDir dir;
	dir.mkdir("mods");
	dir.cd("mods");

	dir.mkdir("coremods");
	writeT("CoreMod", coremods);

	dir.mkdir("mods");
	writeT("Mod", mods);

	dir.mkdir("resources");
	writeT("ResourcePack", packs);

	dir.mkdir("unknown");
	writeT("Unknown", unknown);
}

void LParser::writeT(QString type, QStringList* list){
	lLogD("Moving " + type + "s");
	for(QString name : *list){
		lLogD(getTDir(name) + " to " + getDir(type, name));
		if(!QDir().rename(getTDir(name) , getDir(type, name))){
			lLogE("Move " + type + " " + name + " failed");
		}
	}
}
//  Write


void LParser::clear(){
	QDir t("downloads");

	QStringList l;l << "*.*";
	for(QFileInfo s : t.entryInfoList(l)){
		QFile(s.absoluteFilePath()).remove();
	}

	t = QDir("tmp");
	t.removeRecursively();
	lLogD("Clearing tmp/ and downloads/ ");
}


inline QString LParser::getTDir(QString name){
	static QString s = QDir().absolutePath() + "/";
	return s + "tmp/" + name;
}

inline QString LParser::getDir(QString type, QString name){
	static QString s = QDir().absolutePath() + "/";
	QString t;
	if(type == "Coremod"){
		t = "mods/coremods/";
	}else if(type == "Mod"){
		t = "mods/mods/";
	}else if(type == "ResourcePack"){
		t = "mods/resources/";
	}else{
		t = "mods/unknown/";
	}
	return s + t + name;
}

inline LZipEntry LParser::search(QString n){
	for(LZipEntry e : *list){
		if(e.name == n) return e;
	}
	return not_found;
}
// LParser