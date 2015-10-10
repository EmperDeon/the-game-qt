#include <Global/gmods.h>

#undef CLASS_NAME
#define CLASS_NAME "Modloader"
GMods::GMods(){
	initModLoaders();
}

void GMods::coreInit(){
	if(modloader){
		this->modloader->corePreInit();
		this->modloader->coreInit();
		this->modloader->corePostInit();
	}
}

void GMods::init(){
	if(modloader){
		this->modloader->preInit();
		this->modloader->init();
		this->modloader->postInit();
	}
}

void GMods::initModLoaders() {
	QDir modloaderdir("modloaders");
	QPluginLoader pluginLoader("modLoader");
	QObject *plugin = pluginLoader.instance();
	if (plugin) {
		GModLoaderInterface* t = qobject_cast<GModLoaderInterface *>(plugin);
		if (t){
			modloader = t;
			modloader->setVars(GV_VARS);
			logI(modloader->getName() + " modloader loaded");
		}
	}
}
