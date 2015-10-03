#include "mmodloader.h"

QString ModLoader::getName(){
	return "BaseModLoader";
}

void ModLoader::setVars(IVars *v) {
	this->vars = v;
	this->log = reinterpret_cast<ILogger*>(vars->get("elogger"));

	this->lmods = new QList<IMod*>;
	this->lcmods = new QList<ICoreMod*>;

	this->jsons = new QList<QJsonObject>;

	this->parser = new MParser(this);

	log->log(GLogLevel::INFO, "Main", "ModLoader Inited");
}

void ModLoader::corePreInit(){
	parser->parse();
	QStringList owr;
			foreach(QJsonObject o, *jsons){
			if(o.contains("owerwr")){
						foreach(QJsonValue a, o["owerwr"].toArray()){
						owr << a.toString();
					}
			}
		}
	owr << "render";

	vars->setOverwriteList(owr);

	this->render = new MRender(this);
	this->log->log(GLogLevel::FINE, "Main", "corePreInit finished");
}
void ModLoader::coreInit(){
	render->init();
	this->log->log(GLogLevel::FINE, "Main", "coreInit finished");
}
void ModLoader::corePostInit(){

	this->log->log(GLogLevel::FINE, "Main", "corePostInit finished");
}

void ModLoader::preInit(){

	this->log->log(GLogLevel::FINE, "Main", "preInit finished");
}
void ModLoader::init(){
//
//	QTime t, t1;
//	t.start();
////hash - 387 mb, 8 sec
//	QString ts;
// for(int m = 0 ; m < 16 ; m++)
//	 for(int i = 0 ; i < 256 ; i++)
//		 for(int k = 0 ; k < 256 ; k++)
//			 for(int s = 0 ; s < 2 ; s++){
//				 ts = "mod" + QString::number(m) +
//						 "item" + QString::number(i) +
//						 "kind" + QString::number(k) +
//						 "state" + QString::number(s);
//			  map[ts] = new Emiks(m,i,k,s);
//			 }
//
//	int j = t.elapsed();
//	t1.start();

//	this->log->log(GLogLevel::INFO, "Main", "added in: "+QString::number(j) +	", getted in " + QString::number(t1.elapsed()));
	QMap<QString, quint32>* tm  = new QMap<QString, quint32>;
	for(quint32 i = 0 ; i < 131072 ; i++)
		tm->insert(QString::number(i)+"^"+QString::number(i)+"^"+QString::number(i)+"^"+QString::number(i), i);

	this->log->log(GLogLevel::FINE, "Main", "init finished");
}

void ModLoader::postInit(){
	this->log->log(GLogLevel::FINE, "Main", "postInit finished");
}

void ModLoader::addModInstance(QJsonObject o) {
	if(o["type"].toString() == "Mod"){
		if(o.contains("ftxt")){

		}else if(o.contains("fscr")){

		}else if(o.contains("fplg")){
   *(this->lmods) << qobject_cast<IMod*>(instance(""+o["fplg"].toString()));
		}
	}
}
void ModLoader::addCoreModInstance(QJsonObject o) {
	if(o["type"].toString() == "CoreMod"){

	}
}

QObject *ModLoader::instance(QString f) {
		QPluginLoader pluginLoader(f);
		return pluginLoader.instance();
}
