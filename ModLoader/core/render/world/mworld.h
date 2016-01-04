#ifndef GLOBALQT_MWORLD_H
#define GLOBALQT_MWORLD_H
#include <ModLoader/mdefines.h>
#include <ModLoader/core/mcoremods.h>
#include <ModLoader/core/render/mhelper.h>

class MWorldRender : public IWorldRender, public MRHelper{// 3D
	QString className = "M-WorldRender";
	MCoreMods* loader;
 ILevelManager* manager;
	ILevel* level;

	void drawAxis();
public:
	MWorldRender(MCoreMods* m);
	virtual void init();
	virtual void render();

	virtual void close();
};


#endif //GLOBALQT_MWORLD_H
