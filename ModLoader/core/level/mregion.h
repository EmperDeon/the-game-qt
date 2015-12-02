#ifndef GLOBALQT_MREGION_H
#define GLOBALQT_MREGION_H
#include <ModLoader/mdefines.h>
#include <ModLoader/core/level/mchunk.h>

class MRegion : public IRegion{
	static const int xSize = 8;
	static const int ySize = 8;
	static const int zSize = 8;

	IChunk* reg[xSize][ySize][zSize];
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
	void setChunk(IChunk *ch);
	void read();
	void write();
	void write(IChunk* ch, QDataStream& out);
	void rewrite();
};


#endif //GLOBALQT_MREGION_H
