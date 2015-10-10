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
	mLogF("preInit finished");
}

void MMods::init() {
	this->text->  init();
	this->script->init();
	this->plugin->init();
	mLogF("init finished");
}

void MMods::postInit() {
	this->text->  postInit();
	this->script->postInit();
	this->plugin->postInit();
	mLogF("postInit finished");
}
