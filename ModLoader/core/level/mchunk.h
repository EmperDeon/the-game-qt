#ifndef GLOBALQT_MCHUNK_H
#define GLOBALQT_MCHUNK_H
#include <ModLoader/mdefines.h>
#include <ModLoader/core/level/mblock.h>

class MChunk : public IChunk{
	IWorldBlock* chunk[size][size][size];
 IAChunkPos id;

	//RenderList
	byte rSides[size][size][size];
	GLuint rList;

	void reParseSides();
	void drawCube(int x, int y, int z);

public:
	MChunk();
	MChunk(IWorldGenerator *gen, IAChunkPos p);
	MChunk(QByteArray a, QJsonObject o, IAChunkPos pos);

	virtual IAChunkPos   getId()                                 override {return id;}
	virtual IWorldBlock* getBlock(IBlockPos p)                   override;
	virtual void         setBlock(IWorldBlock* b)                override;
	virtual void         setBlock(IBlockPos pos, IWorldBlock *b) override;
	virtual void         write(QDataStream &a, QJsonObject& o)   override;

	virtual void   setGlList(GLuint i) override {this->rList = i;}
	virtual GLuint getGlList()         override {return this->rList;}
	virtual void   onReAlloc()         override;


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

	virtual QColor getBlockColor(IBlockPos pos) override;
	virtual void   setGlList(GLuint i)          override {this->list = i;}
	virtual GLuint getGlList()                  override {return this->list;}
	virtual void   onReAlloc()                  override;
};

#endif //GLOBALQT_MCHUNK_H
