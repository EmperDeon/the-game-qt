#ifndef GLOBALQT_MCHUNK_H
#define GLOBALQT_MCHUNK_H
#include <ModLoader/mdefines.h>
#include <ModLoader/core/level/mblock.h>

class MChunk : public IChunk{
	static const int size = 32;
	IWorldBlock* chunk[size][size][size];
 IChunkPos id;
	int c;
public:
	MChunk();
	MChunk(IChunkPos p);
	MChunk(QByteArray a, QJsonObject o, IChunkPos pos);
 int getType();
	virtual IChunkPos getId();
	virtual IWorldBlock *getBlock(IBlockPos p);
	virtual void setBlock(IWorldBlock* b);
	void write(QDataStream &a, QJsonObject& o);
};

class MPChunk : public IPChunk{

public:
	MPChunk();

	virtual QColor getBlockColor(IBlockPos pos);
};

#endif //GLOBALQT_MCHUNK_H
