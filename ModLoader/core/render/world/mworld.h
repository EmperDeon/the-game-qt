#ifndef GLOBALQT_MWORLD_H
#define GLOBALQT_MWORLD_H
#include <ModLoader/mdefines.h>
#include <ModLoader/core/render/mhelper.h>
#include <ModLoader/core/mcoremods.h>

class MGlWidget;

class MWorldRender : public IWorldRender, public MRHelper{// 3D
	// Level
	QMutex* listMutex;
	MGlWidget* widget;
	ILevelManager* manager;
	ILevel* level;
	bool currentGened = false;
	GLuint currentIndex = 0;
	int currentGenCount = 0;
 int currentActive = 0;

	//Player
	IEntity* en;
	int renderDistance;
	qint32 eCX = -1, eCZ = 0;
	QMap<IAChunkPos, int>* chunks;
	QList<int>* renderLists;

	void drawAxis();
 void selectBlock();
 void checkPos();
	inline bool isInRange(qint32 x, qint32 z){return
//			x < renderDistance && x > -renderDistance  &&
//			z < renderDistance && z > -renderDistance ;
		sqrt(x*x + z*z) < renderDistance;
	}
public:
	MWorldRender();
	virtual void init();
	virtual void render();

	virtual void close();
	virtual void setPlayer(IEntity* e){this->en = e;};
	// Level-relative
	virtual void setChunks(QMap<IAChunkPos, IChunk*>* ch);
	virtual void reAllocate(int i);
	virtual GLuint getFreeList();
};


#endif //GLOBALQT_MWORLD_H
