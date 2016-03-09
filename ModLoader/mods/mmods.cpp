#include <ModLoader/mods/mmods.h>

#define upd(a) main->setSplashLabel(a)

MMods::MMods(){
	this->text   = new MTextContainer   ();
	this->script = new MScriptsContainer();
	this->plugin = new MPluginsContainer();
}
void testPos(int x, int y, int z){
	IAChunkPos p(x,y,z);
	if(
		 (x != p.x())||
			(y != p.y())||
			(z != p.z())
		)
	logI(QString("O: %1 %2 %3, P: %4 %5 %6").arg(x, 2).arg(y, 2).arg(z, 2).arg(p.x(), 2).arg(p.y(), 2).arg(p.z(), 2));
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

//	for(int x = -20 ; x < 20 ; x++)
//	for(int y = -20 ; y < 20 ; y++)
//	for(int z = -20 ; z < 20 ; z++)
//				testPos(x,y,z);
}

MMods* MV_MODS;