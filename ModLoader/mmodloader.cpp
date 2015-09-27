#include "mmodloader.h"
#include "mrender.h"

QString ModLoader::getName(){
	return "BaseModLoader";
}

void ModLoader::setVars(IVars *v) {
 this->vars = v;
	this->log = reinterpret_cast<ILogger*>(vars->get("elogger"));
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

	this->log->log(GLogLevel::FINE, "Main", "init finished");
}
void ModLoader::postInit(){

	this->log->log(GLogLevel::FINE, "Main", "postInit finished");
}


