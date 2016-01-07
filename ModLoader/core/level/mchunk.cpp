#include "ModLoader/core/level/mchunk.h"
#include <ModLoader/core/render/mhelper.h>

MChunk::MChunk(){}
MChunk::MChunk(IChunkPos p): id(p){
	for(int x = 0 ; x < size; x++)
		for(int y = 0 ; y < size ; y++)
			for(int z = 0 ; z < size ; z++)
				if(y > 24){
					if(rand() % 2 == 0) {
						chunk[x][y][z] = new MWorldBlock(Imiks(1, 1, 1, 1), IBlockPos(x, y, z));
					}
				}else{
					chunk[x][y][z] = NULL;
				}

}
MChunk::MChunk(IWorldGenerator *gen, IChunkPos p): id(p){ gen->generateChunk(this);}
MChunk::MChunk(QByteArray a, QJsonObject o, IChunkPos pos): id(pos){
	quint32 id;
	int pr, type;
	QJsonArray arr = o["params"].toArray();
	QDataStream in(a);
	in.setVersion(QDataStream::Qt_5_4);

	in >> type;
	for ( int x = 0; x < size; x++ )		for ( int y = 0; y < size; y++ )			for ( int z = 0; z < size; z++ ){
				in >> id;
				in >> pr;
				if(id == 0 ){
					this->chunk[x][y][z] = NULL;
				}else if(pr == 0){
					this->chunk[x][y][z] = new MWorldBlock(
						Imiks(id),
						IBlockPos(x, y, z)
					);
				}else{
					this->chunk[x][y][z] = new MWorldBlock(
						Imiks(id),
						IBlockPos(x, y, z),
						arr.at(pr).toString()
					);
				}
			}
}
IChunkPos MChunk::getId() {	return this->id;}
IWorldBlock *MChunk::getBlock(IBlockPos p) { return chunk[p.x()][p.y()][p.z()];}
void MChunk::setBlock(IWorldBlock* b){ this->chunk[b->getPos().x()][b->getPos().y()][b->getPos().z()] = b;}
void MChunk::setBlock(IBlockPos pos, IWorldBlock *b) {this->chunk[pos.x()][pos.y()][pos.z()] = b;}
void MChunk::write(QDataStream& out, QJsonObject& o) {
	QJsonArray arr;

	for ( int x = 0; x < size; x++ )
		for ( int y = 0; y < size; y++ )
			for ( int z = 0; z < size; z++ ) {
				if(chunk[x][y][z] == nullptr){
					out << int(0) << int(0);
				}else	if (chunk[x][y][z]->isParams()) {
					arr << chunk[x][y][z]->getParams();
					out << chunk[x][y][z]->getId().c() << arr.size();
				} else {
					out << chunk[x][y][z]->getId().c() << int(0);
				}
			}

	QJsonObject obj;
	obj["params"] = arr;
	o["chunk"
	  +QString::number(this->id.x())
	  +QString::number(this->id.y())
	  +QString::number(this->id.z())
	] = obj;
}
void MChunk::setGlList(GLuint i) {	this->rList = i;}

void MChunk::reParseSides(){
	for(int x = 0 ; x < size ; x++)
		for(int y = 0 ; y < size ; y++)
			for(int z = 0 ; z < size ; z++){
				setNSides(x, y, z);
			}

//	for(int x = 1 ; x < size-1 ; x++)
//		for(int y = 1 ; y < size-1 ; y++)
//			for(int z = 1 ; z < size-1 ; z++)
//				if(chunk[x][y][z] == nullptr){
//					setVSides(x, y, z);
//				}
}
void MChunk::setNSides(int x, int y, int z){
	if(chunk[x][y][z] != nullptr) {
		if((x > 0)    && (chunk[x - 1][y][z] == nullptr)){ rSides[x][y][z] |= IBSides::Left;		}
		if((x < size) && (chunk[x + 1][y][z] == nullptr)){ rSides[x][y][z] |= IBSides::Right;		}
		if((y > 0)    && (chunk[x][y - 1][z] == nullptr)){ rSides[x][y][z] |= IBSides::Bottom;		}
		if((y < size) && (chunk[x][y + 1][z] == nullptr)){ rSides[x][y][z] |= IBSides::Top;		}
		if((z > 0)    && (chunk[x][y][z - 1] == nullptr)){ rSides[x][y][z] |= IBSides::Back;		}
		if((z < size) && (chunk[x][y][z + 1] == nullptr)){ rSides[x][y][z] |= IBSides::Front;		}
	}else{
		rSides[x][y][z] = 0;
	}
}
void MChunk::setVSides(int x, int y, int z){
 rSides[  x  ][ y+1 ][  z  ] |= IBSides::Top;
	rSides[  x  ][ y-1 ][  z  ] |= IBSides::Bottom;
	rSides[  x  ][  y  ][ z+1 ] |= IBSides::Left;
	rSides[  x  ][  y  ][ z-1 ] |= IBSides::Right;
	rSides[ x+1 ][  y  ][  z  ] |= IBSides::Front;
	rSides[ x-1 ][  y  ][  z  ] |= IBSides::Back;
}
void MChunk::onReAlloc() {
 // TODO: Render

	reParseSides();

 glNewList(rList, GL_COMPILE);
	for(int x = 0 ; x < size ; x++)
		for(int y = 0 ; y < size ; y++)
			for(int z = 0 ; z < size ; z++)
			if(rSides[x][y][z] != 0){
				MRHelper::drawCubeS(getBlockPos(x, y, z), rSides[x][y][z], rc);
			}

	glEndList();
}


MPChunk::MPChunk(){}
QColor MPChunk::getBlockColor(IBlockPos pos) {	return QColor(Qt::gray);}


void MPChunk::setGlList(GLuint i) { this->list = i;}

void MPChunk::onReAlloc() {
	// TODO: Render
}
