#include "mparser.h"

MParser::MParser(ModLoader *m) {
 this->loader = m;
}

void MParser::parse() {
 parse("mods/coremods");
	parse("mods/mods");
}
void MParser::parse(QString s){
 QDir dir(s);
	foreach(QFileInfo i, dir.entryInfoList(QDir::Dirs | QDir::NoDotAndDotDot)){
		*(loader->jsons) << loadJson(QDir(s+"/"+i.fileName()).filePath("pack.dat"));
		}
}
