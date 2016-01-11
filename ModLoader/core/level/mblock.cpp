#include <ModLoader/core/level/mblock.h>

MWorldBlock::MWorldBlock():id(), pos(), param(""){}

MWorldBlock::MWorldBlock(Imiks i, IBlockPos p): id(i), pos(p), param("") {}

MWorldBlock::MWorldBlock(Imiks i, IBlockPos p, QString par):id(i),pos(p),param(par){}
