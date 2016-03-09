#include <ModLoader/mods/mmods.h>

#define upd(a) main->setSplashLabel(a)

MMods::MMods(){
	this->text   = new MTextContainer   ();
	this->script = new MScriptsContainer();
	this->plugin = new MPluginsContainer();
}

void MMods::preInit() {
	main = varG(IMain*, "eMain");
	
	logFF("preInit started");
 this->text->  preInit();
	this->script->preInit();
	this->plugin->preInit();
	logFF("preInit finished");

}

void MMods::init() {
	logFF("init started");
	this->text->  init();
	this->script->init();
	this->plugin->init();
	logFF("init finished");
}

void MMods::postInit() {
	logFF("postInit started");
	this->text->  postInit();
	this->script->postInit();
	this->plugin->postInit();
	logFF("postInit finished");

	varG(IWorldRender*, "mWorldRender")->reAllocate(1025);
}

MMods* MV_MODS;