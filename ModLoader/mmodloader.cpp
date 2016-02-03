#include <ModLoader/mmodloader.h>

QString MModLoader::getName(){
	return "BaseModLoader";
}

void MModLoader::setVars(IVars *v) {
	MV_LOGGER = reinterpret_cast<ILogger*>(v->get("eLogger"));

	MV_VARS = v;
 MV_SETT = reinterpret_cast<ISettings*>(v->get("eSettings"));
	MV_SETC = reinterpret_cast<ISettCont*>(v->get("eSettCont"));

	MV_CORE_MODS = new MCoreMods();
	MV_MODS = new MMods();

	mLogD("ModLoader Inited");
}

void MModLoader::corePreInit(){  MV_CORE_MODS->preInit(); }
void MModLoader::coreInit(){     MV_CORE_MODS->init();    }
void MModLoader::corePostInit(){	MV_CORE_MODS->postInit();}

void MModLoader::preInit(){	 MV_MODS->preInit();}
void MModLoader::init(){	    MV_MODS->init();}
void MModLoader::postInit(){	MV_MODS->postInit(); }

ILogger*   MV_LOGGER;
IVars*     MV_VARS;
ISettings* MV_SETT;
ISettCont* MV_SETC;
