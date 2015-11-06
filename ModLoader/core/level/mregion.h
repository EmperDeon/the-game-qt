#ifndef GLOBALQT_MREGION_H
#define GLOBALQT_MREGION_H
#include <ModLoader/mdefines.h>
#include <ModLoader/core/level/mchunk.h>

class MRegion : public IRegion{
	static const int xSize = 8;
	static const int ySize = 8;
	static const int zSize = 8;

	MChunk* reg[xSize][ySize][zSize];
	IRegionPos pos;
 QString file;

public:
	MRegion(IRegionPos p, QString name);
	IRegionPos getId();
	IChunk* getChunk(IChunkPos p);
	void read();
	void write();
};


#endif //GLOBALQT_MREGION_H
