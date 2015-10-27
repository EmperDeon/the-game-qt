#ifndef GLOBALQT_ILEVEL_H
#define GLOBALQT_ILEVEL_H
class Imiks;

class IWorldBlock {
public:
	virtual Imiks getId() = 0;
	virtual IBlockPos getPos() = 0;
	virtual QString getParams() = 0;
	virtual void addParam(QString s) = 0;
	virtual void setParam(QString s) = 0;
	virtual bool isParams() = 0;
};

class IRegon{

};

class IChunk{
public:
	virtual IChunkPos getId() = 0;
	virtual IWorldBlock* getBlock(IBlockPos p) = 0;
	virtual void read(QByteArray a) = 0;
	virtual void write(QDataStream &a) = 0;
//	virtual void load(QDataStream& a) = 0;
//	virtual void save(QDataStream& a) = 0;
};


#endif //GLOBALQT_ILEVEL_H
