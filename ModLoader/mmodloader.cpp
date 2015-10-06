#include "mmodloader.h"

QString ModLoader::getName(){
	return "BaseModLoader";
}

void ModLoader::setVars(IVars *v) {
	this->vars = v;
	this->log = reinterpret_cast<ILogger*>(vars->get("elogger"));

	this->core = new MCoreMods(this);
	this->mods = new MMods(this);

	log->log(GLogLevel::INFO, "Main", "ModLoader Inited");
}

void ModLoader::corePreInit(){  core->preInit(); }
void ModLoader::coreInit(){     core->init();    }
void ModLoader::corePostInit(){	core->postInit();}

void ModLoader::preInit(){	 mods->preInit();}
void ModLoader::init(){	    mods->init();}
void ModLoader::postInit(){	mods->postInit();}
