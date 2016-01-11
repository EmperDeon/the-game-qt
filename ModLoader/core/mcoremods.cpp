#include <ModLoader/core/mcoremods.h>

#define upd(a) main->setSplashLabel(a)

MCoreMods::MCoreMods(){
 this->plugins = new QList<ICoreMod*>;
	this->t_ren = mVarG(QThread*, "eRenderThread");
	this->queue = mVarG(QThreadPool*, "eThreadQueue");
}


// PreInit
void MCoreMods::parseOwerwrites(){
	QDir dir("mods/coremods");
	QStringList owr;

			for(QFileInfo i : dir.entryInfoList(QDir::Dirs | QDir::NoDotAndDotDot)){
			QJsonObject o = loadJson(QDir("mods/coremods/"+i.fileName()).filePath("pack.dat"));
			if(o.contains("owerwr")){
						for(QJsonValue a : o["owerwr"].toArray()){
						owr << a.toString();
					}
			}
		}

	owr << "mRender";
 owr << "mLevel";

	MV_VARS->setOverwriteList(owr);
}

void MCoreMods::loadPlugins() {

}

void MCoreMods::preInit() {
	mLogFF("preInit started");

	main = mVarG(IMain*, "eMain");
 upd("Started preCoreInit");

	parseOwerwrites();
 loadPlugins();
	upd("Plugins Loaded");

	this->level = new MLevelManager();
	mVarS(level, "mLevel");
	upd("Level constructed");

	this->render = new MGlWidget();
	this->render->moveToThread(this->t_ren);
	mVarS(render, "mRender");
	upd("Render constructed");

	this->perf = new MPerfomanceWidget();
	upd("PerfomanceWidget constructed");
	this->perf->show();

	this->actions = new MActions();
	mVarS(actions, "mActions");
	upd("Actions constructed");


	for(ICoreMod* p : *plugins){
	 p->preInit();
	}
	upd("Coremods preInit finished");

	mLogFF("preInit finished");
}
// PreInit


void MCoreMods::init() {
	mLogFF("init started");

	for(ICoreMod* p : *plugins){
		p->init();
	}
	upd("Coremods init finished");

	mLogFF("init finished");
}

void MCoreMods::postInit() {
	mLogFF("postInit started");

	for(ICoreMod* p : *plugins){
 	p->postInit();
	}
	upd("Coremods postInit finished");

	mLogFF("postInit finished");
}

MCoreMods* MV_CORE_MODS;
