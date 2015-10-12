#include "mcoremods.h"

MCoreMods::MCoreMods(ModLoader *l) : loader(l), log(l->log), vars(l->vars){
 this->plugins = new QList<ICoreMod*>;
}

void MCoreMods::parseOwerwrites(){
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

	owr << "mRender";

	vars->setOverwriteList(owr);
}
void MCoreMods::loadPlugins() {

}
void MCoreMods::preInit() {
	mLogFF("preInit started");
	parseOwerwrites();
 loadPlugins();

	this->render = new MRender(this);
	mVarS(render, "mRender");

	foreach(ICoreMod* p, *plugins){
	 p->preInit();
	}

	mLogFF("preInit finished");
}

void MCoreMods::init() {
	mLogFF("init started");

	foreach(ICoreMod* p, *plugins){
		p->init();
	}

	mLogFF("init finished");
}

void MCoreMods::postInit() {
	mLogFF("postInit started");

	foreach(ICoreMod* p, *plugins){
 	p->postInit();
	}

	mLogFF("postInit finished");
}


