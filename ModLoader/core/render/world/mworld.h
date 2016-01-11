#ifndef GLOBALQT_MWORLD_H
#define GLOBALQT_MWORLD_H
#include <ModLoader/mdefines.h>
#include <ModLoader/core/render/mhelper.h>
#include <ModLoader/core/mcoremods.h>

class MWorldRender : public IWorldRender, public MRHelper{// 3D
	// Level
	QMutex* listMutex;
	ILevelManager* manager;
	ILevel* level;
	bool currentGened = false;
	GLuint currentIndex = 0;
	int currentGenCount = 0;
 int currentActive = 0;

	//Player
	IEntity* en;

	void drawAxis();
 void selectBlock();

public:
	MWorldRender();
	virtual void init();
	virtual void render();

	virtual void close();
	virtual void setPlayer(IEntity* e){this->en = e;};
	// Level-relative
	virtual void reAllocate(int i);
	virtual GLuint getFreeList();
};


#endif //GLOBALQT_MWORLD_H
