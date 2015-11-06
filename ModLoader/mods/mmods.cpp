#include "mmods.h"

MMods::MMods(ModLoader *l) : loader(l), log(l->log), vars(l->vars){
	this->text   = new MTextContainer   (this);
	this->script = new MScriptsContainer(this);
	this->plugin = new MPluginsContainer(this);
}

void MMods::preInit() {
//	mLogFF("preInit started");
// this->text->  preInit();
//	this->script->preInit();
//	this->plugin->preInit();
//	mLogFF("preInit finished");
}

QString toHex(QByteArray a){
 QString r, t(a.toHex());
	for(int i = 0, j = 0 ; i < t.length() ; i++){
		if(i  % 4 == 0)
			r += ' ';
		r += t[i];
	}

	return r;
}
QString toHex(QJsonObject o){
	return toHex(QJsonDocument(o).toBinaryData());
}

void MMods::init() {
//	mLogFF("init started");
//	this->text->  init();
//	this->script->init();
//	this->plugin->init();
//	mLogFF("init finished");

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

 QTime t;
	t.start();
	l = new MLevel("test2");
	int i = t.elapsed();
	mLogI("Creating Finished in "+QString::number(i/1000) + "." + QString::number(i%1000));

	t.start();
	l->load();
	i = t.elapsed();
	mLogI("Loading finished in "+QString::number(i/1000) + "." + QString::number(i%1000));

//	t.start();
//	 l->save();
//	i = t.elapsed();
//	mLogI("Saving finished in "+QString::number(i/1000) + "." + QString::number(i%1000));

 //*/
}

void MMods::postInit() {
//	mLogFF("postInit started");
//	this->text->  postInit();
//	this->script->postInit();
//	this->plugin->postInit();
//	mLogFF("postInit finished");
}
