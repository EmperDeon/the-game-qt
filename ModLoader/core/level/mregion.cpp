#include <ModLoader/core/level/mregion.h>

MRegion::MRegion(IRegionPos p, QString name) { // saves/name/dim0/ for name "name" and 0 dimension
 this->pos = p;                                // saves/name/dim0/reg00.dat for id 0 0
	this->file = name+
		"regions" + QString::number(int(p.x() / 128)) + QString::number(int(p.x() / 128)) + "/" +
		"reg" + QString::number(pos.x())+QString::number(pos.y()) + ".dat";

 QDir t(name);
	t.mkdir("regions" + QString::number(int(p.x() / 128)) + QString::number(int(p.x() / 128)));

//	for ( int x = 0; x < xSize; x++ )
//		for ( int y = 0; y < ySize; y++ )
//			for ( int z = 0; z < zSize; z++ )
//				reg[x][y][z] = new MChunk(IChunkPos(x, y, z));

}
IRegionPos MRegion::getId() {	return pos;}
IChunk* MRegion::getChunk(IChunkPos p) {	return reg[p.x()][p.y()][p.z()];}
void MRegion::write() {
 QFile o(file);
	QJsonObject obj;

 o.open(QFile::WriteOnly);
	QDataStream out(&o);
 out.setVersion(QDataStream::Qt_5_4);

	for ( int x = 0; x < xSize; x++ )
		for ( int y = 0; y < ySize; y++ )
			for ( int z = 0; z < zSize; z++ )
			 if(reg[x][y][z] != NULL){
				 QByteArray ta;
			 	QDataStream ts(&ta, QIODevice::WriteOnly);
			 	reg[x][y][z]->write(ts, obj);

			 	out << ta.size() << ta;
		 	}

	QByteArray outa;
	QByteArray arr(QJsonDocument(obj).toBinaryData());
	QDataStream outs(&outa, QIODevice::WriteOnly);

	o.flush();
	o.close();
	o.open(QFile::ReadOnly);

 outs << arr.size() << arr << o.readAll();

	o.close();
 o.open(QFile::WriteOnly);

	o.write(qCompress(outa, 1));
 o.flush();
	o.close();
}
void MRegion::read() {
 QFile i(file);
	i.open(QFile::ReadOnly);
	QByteArray ar(qUncompress(i.readAll()));
	QDataStream in(&ar, QIODevice::ReadOnly);

	int size;
	char* ch;

	in >> size;
	ch = new char[size];
	in.skipRawData(4);
	in.readRawData(ch, size);
	QJsonObject obj = QJsonDocument::fromBinaryData(QByteArray(ch, size)).object();
 delete[] ch;

	for ( int x = 0; x < xSize; x++ )
		for ( int y = 0; y < ySize; y++ )
			for ( int z = 0; z < zSize; z++ ) {

				in.skipRawData(4);
				in >> size;
				ch = new char[size];
				in.readRawData(ch, size);

				reg[x][y][z] = new MChunk(
					QByteArray(ch, size),
					obj["chunk"+QString::number(x)+QString::number(y)+QString::number(z)].toObject(),
				 IChunkPos(x, y, z)
				);

    delete[] ch;
			}

	i.close();
}


