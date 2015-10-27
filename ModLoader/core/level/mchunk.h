#ifndef GLOBALQT_MCHUNK_H
#define GLOBALQT_MCHUNK_H
#include <ModLoader/mdefines.h>

class MWorldBlock : public IWorldBlock{
	Imiks id;
	IBlockPos pos;
	QString param;
public:
	MWorldBlock();
	MWorldBlock(Imiks i, IBlockPos p);
	MWorldBlock(Imiks i, IBlockPos p, QString par);

	virtual Imiks getId() override;
	virtual IBlockPos getPos() override;
	virtual QString getParams();
	virtual void addParam(QString s);
	virtual void setParam(QString s);
	virtual bool isParams();
};
class MChunk : public IChunk{
	MWorldBlock chunk[32][32][32];
 IChunkPos id;
public:
	MChunk(IChunkPos p);
 int getType();
	virtual IChunkPos getId();
	virtual IWorldBlock *getBlock(IBlockPos p);
	virtual void read(QByteArray a);
	virtual void write(QDataStream &a);
};

#endif //GLOBALQT_MCHUNK_H
