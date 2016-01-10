#include "mmodloader.h"

QString MModLoader::getName(){
	return "BaseModLoader";
}

void MModLoader::setVars(IVars *v) {
	this->loader = this;
	this->vars = v;
	this->log = reinterpret_cast<ILogger*>(vars->get("eLogger"));

	MV_LOGGER = this->log;
	MV_VARS = this->vars;

	this->core = new MCoreMods(this);
	this->mods = new MMods(this);

	MV_CORE_MODS = this->core;
	MV_MODS = this->mods;

	mLogD("ModLoader Inited");
}

void MModLoader::corePreInit(){  core->preInit(); }
void MModLoader::coreInit(){     core->init();    }
void MModLoader::corePostInit(){	core->postInit();}

void MModLoader::preInit(){	 mods->preInit();}
void MModLoader::init(){	    mods->init();}
void MModLoader::postInit(){	mods->postInit(); }

ILogger* MV_LOGGER;
IVars* MV_VARS;