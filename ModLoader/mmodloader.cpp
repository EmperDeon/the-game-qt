#include "mmodloader.h"

QString ModLoader::getName(){
	return "BaseModLoader";
}
void ModLoader::parseZips(){
	parser->parseZip();
}

void ModLoader::setLogger(LLogWidget* log){
	this->w_log = log;
	modsMap = new MModsList(this);
	parser = new Parser(this);
	w_mod = new MModsWidget(this);
	w_mode = new MModEditor(this);
	w_pack = new MPacker(this);
}
void ModLoader::showMods(){
	this->w_mod->show();
}
void ModLoader::showModEditor(){
	this->w_mode->show();
}
void ModLoader::showPacker(){
	this->w_pack->show();
}

void ModLoader::corePreInit(){

}
void ModLoader::coreInit(){

}
void ModLoader::corePostInit(){

}

void ModLoader::preInit(){

}
void ModLoader::init(){

}
void ModLoader::postInit(){

}
