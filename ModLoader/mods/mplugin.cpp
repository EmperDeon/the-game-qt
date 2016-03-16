#include <mods/mplugin.h>

MPluginsContainer::MPluginsContainer(){
 this->plugins = new QList<IMod*>;
}

void MPluginsContainer::preInit() {
	for(IMod* p : *plugins){
		p->preInit();
	}
}

void MPluginsContainer::init() {
	for(IMod* p : *plugins){
		p->init();
	}
}

void MPluginsContainer::postInit() {
	for(IMod* p : *plugins){
		p->postInit();
	}
}
