#include <emods.h>

// EMods
EMods::EMods(){
	initModLoaders();
}

void EMods::coreInit(){
	logF("CoreInit started");
	if(modloader){
		this->modloader->corePreInit();
		this->modloader->coreInit();
		this->modloader->corePostInit();
	}
	logF("CoreInit finished");
}

void EMods::init(){
	logF("Init started");
	if(modloader){
		this->modloader->preInit();
		this->modloader->init();
		this->modloader->postInit();
	}
	logF("Init finished");
}

void EMods::initModLoaders() {
	QPluginLoader pluginLoader("modLoader");
	QObject* plugin = pluginLoader.instance();
	if (plugin) {
		IModLoader* t = qobject_cast<IModLoader*>(plugin);
		if (t){
			modloader = t;
			modloader->setVars(IV_VARS);
			logI(modloader->getName() + " modloader loaded");
		}
	}
}
// EMods