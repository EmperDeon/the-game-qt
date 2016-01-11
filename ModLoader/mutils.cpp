#include <ModLoader/mutils.h>

QJsonObject loadJson(QString file){
	QFile loadFile(file);
	loadFile.open(QIODevice::ReadOnly);

	QJsonDocument loadDoc(QJsonDocument::fromBinaryData(qUncompress(loadFile.readAll())));
	return loadDoc.object();
}