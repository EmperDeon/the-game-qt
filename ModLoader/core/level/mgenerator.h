#ifndef GLOBALQT_MGENERATOR_H
#define GLOBALQT_MGENERATOR_H
#include <ModLoader/mdefines.h>

class MWorldGenerator : public IWorldGenerator{

public:
	MWorldGenerator();
	virtual void generateChunk(IChunk *ch);
};

#endif //GLOBALQT_MGENERATOR_H
