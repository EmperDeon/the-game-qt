#ifndef GLOBALQT_MBLOCK_H
#define GLOBALQT_MBLOCK_H
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

#endif //GLOBALQT_MBLOCK_H
