#include "mchunk.h"

MWorldBlock::MWorldBlock():id(), pos(), param(""){}
MWorldBlock::MWorldBlock(Imiks i, IBlockPos p): id(i), pos(p), param("") {}
MWorldBlock::MWorldBlock(Imiks i, IBlockPos p, QString par):id(i),pos(p),param(par){}
Imiks MWorldBlock::getId() { return id; }
IBlockPos MWorldBlock::getPos() { return pos; }
QString MWorldBlock::getParams(){ return param; }
void MWorldBlock::addParam(QString s){ this->param += s; }
void MWorldBlock::setParam(QString s){ this->param = s; }
bool MWorldBlock::isParams(){return param == "";}

MChunk::MChunk(IChunkPos p): id(p){
	for(int x = 24 ; x < 32; x++)
		for(int y = 0 ; y < 32 ; y++)
			for(int z = 0 ; z < 32 ; z++)
				if(rand() % 2 == 0)
				 chunk[x][y][z] = MWorldBlock(Imiks(1,1,1,1), IBlockPos(x,y,z));
				else
					chunk[x][y][z] = MWorldBlock(Imiks(1,1,1,1), IBlockPos(x,y,z), "Parameter1;");
}
IChunkPos MChunk::getId() {	return this->id;}
IWorldBlock *MChunk::getBlock(IBlockPos p) { return &chunk[p.x()][p.y()][p.z()];}
int MChunk::getType() {
	int type, c = 0;
	for ( int x = 0; x < 32; x++ )
		for ( int y = 0; y < 32; y++ )
			for ( int z = 0; z < 32; z++ )
				if(chunk[x][y][z].isParams())
					c++;

	if(c == 0) type = 1;
	else if(c <= 256) type = 2;
	else type = 3;

	return type;
}
void MChunk::write(QDataStream& a) {
	QJsonArray arr;
	{
		QByteArray outp;
		QDataStream out(outp);
		out.setVersion(QDataStream::Qt_5_4);
		int type = getType();

		for ( int x = 0; x < 32; x++ )
			for ( int y = 0; y < 32; y++ )
				for ( int z = 0; z < 32; z++ ) {
					if (chunk[x][y][z].isParams()) {
						arr << chunk[x][y][z].getParams();
						out << chunk[x][y][z].getId().c() ;
						switch (type){
							case 1: break;
							case 2: out << (byte)arr.size(); break;
							case 3: out << (int)arr.size(); break;
							default:;
						}
					} else {
						out << chunk[x][y][z].getId().c();
						switch (type){
							case 1: break;
							case 2: out << (byte)0; break;
							case 3: out << (int)0; break;
							default:;
						}
					}
				}

		a << type << outp;
	}{
		QByteArray outp;
		QDataStream out(outp);
		out.setVersion(QDataStream::Qt_5_4);

		QJsonObject obj;
		obj["x"] = id.x();
		obj["y"] = id.y();
		obj["z"] = id.z();
		obj["params"] = arr;

		out << QJsonDocument(obj).toBinaryData();

		a << outp.size() << outp;
	}
}
void MChunk::read(QByteArray a) {
	struct MSmallWorldBlock{quint32 id; int pr;};
	int type;
	MSmallWorldBlock arr[32][32][32];
	QDataStream in(a);
	in.setVersion(QDataStream::Qt_5_4);

	in >> type;
	for ( int x = 0; x < 32; x++ )
		for ( int y = 0; y < 32; y++ )
			for ( int z = 0; z < 32; z++ ){
				in >> arr[x][y][z].id;
				switch(type){
					case 1: arr[x][y][z].pr = 0; break;
					case 2: byte t; in >> t; arr[x][y][z].pr = t; break;
					case 3: in >> arr[x][y][z].pr; break;
					default:;
				}
			}

 in >> type;
	QByteArray json(a.right(type));
	QJsonObject o = QJsonDocument::fromBinaryData(json).object();
	this->id = IChunkPos(o["x"].toInt(), o["y"].toInt(), o["z"].toInt());

	QJsonArray arr1 = o["params"].toArray();

	for ( int x = 0; x < 32; x++ )
		for ( int y = 0; y < 32; y++ )
			for ( int z = 0; z < 32; z++ )
			if(arr[x][y][z].pr == 0){
				this->chunk[x][y][z] = MWorldBlock(
					Imiks(arr[x][y][z].id),
					IBlockPos(x, y, z)
				);
			}else{
				this->chunk[x][y][z] = MWorldBlock(
					Imiks(arr[x][y][z].id),
					IBlockPos(x, y, z),
					arr1.at(arr[x][y][z].pr).toString()
				);
			}
}


