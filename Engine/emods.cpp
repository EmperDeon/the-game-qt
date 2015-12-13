#include "Engine/emods.h"

EMods::EMods(){
	initModLoaders();
}

void EMods::coreInit(){
	if(modloader){
		this->modloader->corePreInit();
		this->modloader->coreInit();
		this->modloader->corePostInit();
	}
}

void EMods::init(){
	if(modloader){
		this->modloader->preInit();
		this->modloader->init();
		this->modloader->postInit();
	}
}

void EMods::initModLoaders() {
	QPluginLoader pluginLoader("modLoader");
	QObject *plugin = pluginLoader.instance();
	if (plugin) {
		IModLoader * t = qobject_cast<IModLoader *>(plugin);
		if (t){
			modloader = t;
			modloader->setVars(GV_VARS);
			logI(modloader->getName() + " modloader loaded");
		}
	}
}
