#ifndef GLOBALQT_MCHUNK_H
#define GLOBALQT_MCHUNK_H
#include <ModLoader/mdefines.h>
#include <ModLoader/core/level/mblock.h>

class MChunk : public IChunk{
	IWorldBlock* chunk[size][size][size];
 IChunkPos id;

	//RenderList
	byte rSides[size][size][size];
	GLuint rList;


	void reParseSides();
	void setVSides(int x, int y, int z);
	void setNSides(int x, int y, int z);
	void drawCube(int x, int y, int z);
public:
	MChunk();
	MChunk(IChunkPos p);
	MChunk(IWorldGenerator *gen, IChunkPos p);
	MChunk(QByteArray a, QJsonObject o, IChunkPos pos);
	virtual IChunkPos getId();
	virtual IWorldBlock *getBlock(IBlockPos p);
	virtual void setBlock(IWorldBlock* b);
	virtual void setBlock(IBlockPos pos, IWorldBlock *b);
	virtual void write(QDataStream &a, QJsonObject& o);

	virtual void setGlList(GLuint i);
	virtual void onReAlloc();


	IVec3 getBlockPos(int x, int y, int z){
		return IVec3(
			this->id.x() * size + x,
			this->id.y() * size + y,
			this->id.z() * size + z
		);}
};

class MPChunk : public IPChunk{
	GLuint list;

public:
	MPChunk();

	virtual QColor getBlockColor(IBlockPos pos);
	virtual void setGlList(GLuint i);
	virtual void onReAlloc();
};

#endif //GLOBALQT_MCHUNK_H
