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
	static const int size = 32;
	IWorldBlock* chunk[size][size][size];
 IChunkPos id;
	int c;
public:
	MChunk(IChunkPos p);
	MChunk(QByteArray a, QJsonObject o, IChunkPos pos);
 int getType();
	virtual IChunkPos getId();
	virtual IWorldBlock *getBlock(IBlockPos p);
	virtual void setBlock(IWorldBlock* b);
	void write(QDataStream &a, QJsonObject& o);
};

#endif //GLOBALQT_MCHUNK_H
