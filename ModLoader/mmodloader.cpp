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

void ModLoader::setVars(GVars *v) {
 this->vars = v;
	//this->log = qobject_cast<GLogger*>(vars->get("logger"));
	this->log = reinterpret_cast<GLogger*>(vars->get("logger"));

	log->log(GLogLevel::INFO, "M-Main", "ModLoader Inited");
}

void ModLoader::corePreInit(){
	this->log->log(GLogLevel::FINE, "M-Main", "corePreInit finished");
}
void ModLoader::coreInit(){
	this->log->log(GLogLevel::FINE, "M-Main", "coreInit finished");
}
void ModLoader::corePostInit(){
	this->log->log(GLogLevel::FINE, "M-Main", "corePostInit finished");
}

void ModLoader::preInit(){
	this->log->log(GLogLevel::FINE, "M-Main", "preInit finished");
}
void ModLoader::init(){
	this->log->log(GLogLevel::FINE, "M-Main", "init finished");
}
void ModLoader::postInit(){
	this->log->log(GLogLevel::FINE, "M-Main", "postInit finished");
}


