#include <ModLoader/mods/mmods.h>

#define upd(a) main->setSplashLabel(a)

MMods::MMods(){
	this->text   = new MTextContainer   ();
	this->script = new MScriptsContainer();
	this->plugin = new MPluginsContainer();
}
#define testPos(x1,y1,z1) {IAChunkPos p(x1,y1,z1); mLogI(QString("C %1 %2 %3, reg %4 %5 %6").arg(p.x()).arg(p.y()).arg(p.z()).arg(p.rX()).arg(p.rY()).arg(p.rZ()));}
void MMods::preInit() {
	main = mVarG(IMain*, "eMain");
	
	mLogFF("preInit started");
 this->text->  preInit();
	this->script->preInit();
	this->plugin->preInit();
	mLogFF("preInit finished");

}

void MMods::init() {
	mLogFF("init started");
	this->text->  init();
	this->script->init();
	this->plugin->init();
	mLogFF("init finished");
}

void MMods::postInit() {
	mLogFF("postInit started");
	this->text->  postInit();
	this->script->postInit();
	this->plugin->postInit();
	mLogFF("postInit finished");

	mVarG(IWorldRender*, "mWorldRender")->reAllocate(1025);
}

MMods* MV_MODS;