#include <ModLoader/mmodloader.h>

QString MModLoader::getName(){
	return "BaseModLoader";
}

void MModLoader::setVars(IVars *v) {
	IV_LOGGER = reinterpret_cast<ILogger*>(v->get("eLogger"));

	IV_VARS = v;
 IV_SETT = reinterpret_cast<ISettings*>(v->get("eSettings"));
	IV_SETC = reinterpret_cast<ISettCont*>(v->get("eSettCont"));

	MV_CORE_MODS = new MCoreMods();
	MV_MODS = new MMods();

	logD("ModLoader Inited");
}

void MModLoader::corePreInit(){  MV_CORE_MODS->preInit(); }
void MModLoader::coreInit(){     MV_CORE_MODS->init();    }
void MModLoader::corePostInit(){	MV_CORE_MODS->postInit();}

void MModLoader::preInit(){	 MV_MODS->preInit();}
void MModLoader::init(){	    MV_MODS->init();}
void MModLoader::postInit(){	MV_MODS->postInit(); }

ILogger*IV_LOGGER;
IVars*IV_VARS;
ISettings*IV_SETT;
ISettCont*IV_SETC;
