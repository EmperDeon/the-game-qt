#include <Engine/emain.h>
#include "mcoremods.h"

#define upd(a) main->setSplashLabel(a)

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
 owr << "mLevel";

	vars->setOverwriteList(owr);
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

	this->render = new MGlWidget(this);
	mVarS(render, "mRender");
	upd("Render constructed");

	this->actions = new MActions(this);
	mVarS(actions, "mActions");
	upd("Actions constructed");

	this->level = new MLevelManager(this);
 mVarS(level, "mLevel");
	upd("Level constructed");

	foreach(ICoreMod* p, *plugins){
	 p->preInit();
	}
	upd("Coremods preInit finished");

	mLogFF("preInit finished");
}

void MCoreMods::init() {
	mLogFF("init started");

	foreach(ICoreMod* p, *plugins){
		p->init();
	}
	upd("Coremods init finished");

	mLogFF("init finished");
}

void MCoreMods::postInit() {
	mLogFF("postInit started");

	foreach(ICoreMod* p, *plugins){
 	p->postInit();
	}
	upd("Coremods postInit finished");

	mLogFF("postInit finished");
}



//	MRegion reg(IRegionPos(0,0), "saves/TestWorld_1/dim0/");
//	reg.write();
//QTime t;
//t.start();
//
//QFile file("saves/TestWorld_1/level.dat");file.open(QIODevice::ReadOnly);
//ILevelInfo* info = MLevelInfo::fromJson(QJsonDocument::fromBinaryData(file.readAll()).object());
////	MLevelInfo* info = new MLevelInfo();
//info->setName("TestWorld_1");
//
//MLevel* level = new MLevel(info);
//
//int i = t.elapsed();
//mLogI("Creating Finished in "+QString::number(i/1000) + "." + QString::number(i%1000));
//t.start();
//
//for ( int x = 0; x < 4; x++ )
//for ( int y = 0; y < 4; y++ )
//for ( int z = 0; z < 3; z++ )
//level->addNewChunk(IChunkPos(x, y, z));
//
//i = t.elapsed();
//mLogI("Filling Finished in "+QString::number(i/1000) + "." + QString::number(i%1000));
//t.start();
//
////	level->save();
//level->load();
//
//i = t.elapsed();
//mLogI("Loading Finished in "+QString::number(i/1000) + "." + QString::number(i%1000));



/*QJsonObject obj;

QByteArray a;
QDataStream out(&a, QIODevice::WriteOnly);

obj["test1"] = 4294967295;
obj["test2"] = 1844674407;
obj["test3"] = 1844674407;

out << QJsonDocument(obj).toBinaryData();

mLogW(toHex(a));

char* ch = new char[a.size()];

QByteArray o1(a);
QDataStream out1(o1);
out1.skipRawData(4);
out1.readRawData(ch, a.size());
QByteArray n(ch, a.size());
mLogW(toHex(n));*/
///*

// QTime t;
//	t.start();
//	l = new MLevel("test2");
//	int i = t.elapsed();
//	mLogI("Creating Finished in "+QString::number(i/1000) + "." + QString::number(i%1000));
//
//	t.start();
//	l->load();
//	i = t.elapsed();
//	mLogI("Loading finished in "+QString::number(i/1000) + "." + QString::number(i%1000));

//	t.start();
//	 l->save();
//	i = t.elapsed();
//	mLogI("Saving finished in "+QString::number(i/1000) + "." + QString::number(i%1000));

//*/