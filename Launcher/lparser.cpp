#include "Launcher/lparser.h"
#define ParserVer "0.1"
//Zip
ZipEntry::ZipEntry(QJsonObject o, QString f){
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
QString ZipEntry::toString(){
	QString dep, owr;
			foreach(QJsonValue e, depn){
			dep += e.toString() + "; ";
		}
			foreach(QJsonValue e, ower) {
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
QString ZipErr::toString(){
	return entr.toString() + " : " + err;
}
bool ZipEntry::isValid(){
	return (rev == ParserVer) && (
			(type == "Mod")||
			(type == "CoreMod")||
			(type == "Resource")||
			(type == "Pack"));
}

//Zip
LParser::LParser(LMainWindow* l){
	list = new QList<ZipEntry>;

	err = new QList<ZipErr>;

	coremods = new QStringList;
	mods = new QStringList;
	packs = new QStringList;
	unknown = new QStringList;

	this->log = l->w_log;

	QJsonObject o;
	o["name"] = "NotFound";
	o["type"] = "NotFound";
	o["desc"] = "NotFound";
	o["devl"] = "NotFound";
	o["site"] = "NotFound";
	o["depend"] = QJsonArray();
	o["version"] = "0";
	o["revision"] = "0";
	not_found = ZipEntry(o,"NotFound");

	log->addL(GLogLevel::DEBUG, "LParser", "Constructed");
}

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

void LParser::addE(ZipEntry e, QDir curr){
	if(e.isValid()){
		if(e.type == "Pack"){

					foreach(QFileInfo f, curr.entryInfoList(QDir::Dirs)){
					ZipEntry t =  ZipEntry(loadJson(QDir("tmp/"+f.fileName()).filePath("archive.dat")),"");
					addE(t,f.dir());
				}

		}else{
			list->append(e);
		}
	}else{
		err->append(ZipErr(e,"Zip is not valid"));
	}
}
void LParser::addToList(ZipEntry e){
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

void LParser::unzipDownloads(){
	QDir down("downloads");
	QDir tmp("");
	tmp.mkdir("tmp");
	tmp.cd("tmp/");

	QFileInfoList downf = down.entryInfoList(QDir::Files);
			foreach(QFileInfo f , downf){
			log->addL(GLogLevel::DEBUG, "LParser", "extracting "+f.filePath());
			QZipReader t("downloads/"+f.fileName());
			tmp.mkdir(f.baseName());
			t.extractAll("tmp/"+f.baseName()+"/");
			down.remove(f.fileName());
		}
}
void LParser::parse(){
	QDir tmp("tmp");
			foreach(QFileInfo f, tmp.entryInfoList(QDir::Dirs | QDir::NoDotAndDotDot)){
			if(f.fileName() != "." && f.fileName() != ".."){
				log->addL(GLogLevel::DEBUG, "LParser", "parsing "+f.filePath());
				ZipEntry t =  ZipEntry(loadJson(QDir("tmp/"+f.fileName()).filePath("pack.dat")), f.fileName());
				addE(t,f.dir());
			}else{
				log->addL(GLogLevel::DEBUG, "LParser", "ignoring "+f.filePath());
			}
		}
}
void LParser::check(){
	QStringList names;
	QStringList depen;
			foreach(ZipEntry e, *list){
			if(!names.contains(e.name)){
				names << e.name;
			}else{
				err->append(ZipErr(e,"Duplicate zip name"));
			}
			if(!e.depn.empty()){
				QString t;
						foreach(QJsonValue v, e.depn){
						t = v.toString();
						if(!depen.contains(t)){
							depen << t;
						}
					}
			}
			addToList(e);
		}
			foreach(QString e, depen){
			if(!names.contains(e)){
				err->append(ZipErr(search(e), "Unsatisfied dependency"));
			}
		}
}
void LParser::showErr(){
			foreach(ZipErr e, *err){
			log->addL(GLogLevel::ERR, "LParser", e.toString());
		}
}

inline QString LParser::getTDir(QString name){
	static QString s = QDir().absolutePath() + "/";
	return s + "tmp/" + name;
}
inline QString LParser::getDir(QString type, QString name){
	static QString s = QDir().absolutePath() + "/";
	QString t;
	if(type == "Coremod"){
		t = "coremods/";
	}else if(type == "Mod"){
		t = "mods/";
	}else if(type == "ResourcePack"){
		t = "resources/";
	}else{
		t = "unknown/";
	}
	return s + t + name;
}
void LParser::write(){
	QDir dir;

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
	log->addL(GLogLevel::DEBUG, "LParser", "Moving "+type+"s");
			foreach(QString name, *list){
			log->addL(GLogLevel::DEBUG, "LParser", getTDir(name) +" to " + getDir(type, name));
			if(!QDir().rename(getTDir(name) , getDir(type, name))){
				log->addL(GLogLevel::ERR, "LParser", "Move " + type + " " + name + " failed");
			}
		}
}
void LParser::clear(){
	log->addL(GLogLevel::DEBUG, "LParser", "Clearing tmp/");
	QDir t("tmp/");
	t.removeRecursively();
	log->addL(GLogLevel::DEBUG, "LParser", "Clearing downloads/");
	t.cdUp();
	t.cd("downloads");
	t.removeRecursively();
}

ZipEntry LParser::search(QString n){
			foreach(ZipEntry e, *list){
			if(e.name == n) return e;
		}
	return not_found;
}
//Zip

//Utils
