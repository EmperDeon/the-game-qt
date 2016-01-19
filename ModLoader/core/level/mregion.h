#ifndef GLOBALQT_MREGION_H
#define GLOBALQT_MREGION_H
#include <ModLoader/mdefines.h>
#include <ModLoader/core/level/mchunk.h>

class MRegion : public IRegion{
	IChunk* reg[REGION_SIZE_X][REGION_SIZE_Y][REGION_SIZE_Z];
	QList<IChunk*>* edited;
	IRegionPos pos;
// read-write
 QString file;
	QJsonObject obj;

public:
	MRegion(IRegionPos p, QString name);

	IRegionPos getId();
	IChunk* getConstChunk(IChunkPos p) const;
	IChunk* getChunk(IChunkPos p);
	void    setChunk(IChunk *ch);

	void read();
	void write();
	void write(IChunk* ch, QDataStream& out);
	void rewrite();
};


#endif //GLOBALQT_MREGION_H
