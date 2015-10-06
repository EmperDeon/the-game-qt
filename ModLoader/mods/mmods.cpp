#include "mmods.h"

MMods::MMods(ModLoader *l) : loader(l), log(l->log), vars(l->vars){
	this->text   = new MTextContainer   (this);
	this->script = new MScriptsContainer(this);
	this->plugin = new MPluginsContainer(this);
}

void MMods::preInit() {
 this->text->  preInit();
	this->script->preInit();
	this->plugin->preInit();
	this->loader->log->log(GLogLevel::FINE, "MMods", "preInit finished");
}

void MMods::init() {
	this->text->  init();
	this->script->init();
	this->plugin->init();
	this->loader->log->log(GLogLevel::FINE, "MMods", "init finished");
}

void MMods::postInit() {
	this->text->  postInit();
	this->script->postInit();
	this->plugin->postInit();
	this->loader->log->log(GLogLevel::FINE, "MMods", "postInit finished");
}
