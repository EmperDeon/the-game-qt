#include "ModLoader/core/level/mblock.h"

MWorldBlock::MWorldBlock():id(), pos(), param(""){}
MWorldBlock::MWorldBlock(Imiks i, IBlockPos p): id(i), pos(p), param("") {}
MWorldBlock::MWorldBlock(Imiks i, IBlockPos p, QString par):id(i),pos(p),param(par){}
Imiks MWorldBlock::getId() { return id; }
IBlockPos MWorldBlock::getPos() { return pos; }
QString MWorldBlock::getParams(){ return param; }
void MWorldBlock::addParam(QString s){ this->param += s; }
void MWorldBlock::setParam(QString s){ this->param = s; }
bool MWorldBlock::isParams(){return param != "";}
