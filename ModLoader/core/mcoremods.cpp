#include "mcoremods.h"

MCoreMods::MCoreMods(ModLoader *l) : loader(l), log(l->log), vars(l->vars){
 this->plugins = new QList<ICoreMod*>;
}

void MCoreMods::parseOwerwrites(){
	QList<QJsonObject> lst;
	QDir dir("mods/coremods");
	QStringList owr;

			foreach(QFileInfo i, dir.entryInfoList(QDir::Dirs | QDir::NoDotAndDotDot)){
			QJsonObject o = loadJson(QDir("mods/coremods/"+i.fileName()).filePath("pack.dat"));
			if(o.contains("owerwr")){
						foreach(QJsonValue a, o["owerwr"].toArray()){
						owr << a.toString();
					}
			}
		}

	owr << "render";

	vars->setOverwriteList(owr);
}
void MCoreMods::loadPlugins() {

}
void MCoreMods::preInit() {
	parseOwerwrites();
 loadPlugins();

	this->render = new MRender(this);
	this->vars->set((IRender*)render, "render");

	foreach(ICoreMod* p, *plugins){
	 p->preInit();
	}

	this->loader->log->log(GLogLevel::FINE, "MCoreMods", "preInit finished");
}

void MCoreMods::init() {
	foreach(ICoreMod* p, *plugins){
		p->init();
	}

	this->loader->log->log(GLogLevel::FINE, "MCoreMods", "init finished");
}

void MCoreMods::postInit() {
	foreach(ICoreMod* p, *plugins){
 	p->postInit();
	}

	this->loader->log->log(GLogLevel::FINE, "MCoreMods", "postInit finished");
}


