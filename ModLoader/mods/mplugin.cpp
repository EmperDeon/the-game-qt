#include "mplugin.h"

MPluginsContainer::MPluginsContainer(MMods *l) : loader(l), log(l->log), vars(l->vars){
 this->plugins = new QList<IMod*>;
}

void MPluginsContainer::preInit() {
	foreach(IMod* p, *plugins){
		p->preInit();
	}
}

void MPluginsContainer::init() {
	foreach(IMod* p, *plugins){
		p->init();
	}
}

void MPluginsContainer::postInit() {
	foreach(IMod* p, *plugins){
		p->postInit();
	}
}
