#ifndef GLOBALQT_MBLOCK_H
#define GLOBALQT_MBLOCK_H
#include <idefines.h>

class MWorldBlock : public IWorldBlock{
	Imiks id;
	IBlockPos pos;
	QString param;

public:
	MWorldBlock();
	MWorldBlock(Imiks i, IBlockPos p);
	MWorldBlock(Imiks i, IBlockPos p, QString par);

	virtual Imiks     getId()             override {return id; }
	virtual IBlockPos getPos()            override {return pos; }
	virtual QString   getParams()         override {return param; }
	virtual void      addParam(QString s) override {this->param += s; }
	virtual void      setParam(QString s) override {this->param = s; }
	virtual bool      isParams()          override {return param != "";}
};

#endif //GLOBALQT_MBLOCK_H
