#ifndef GLOBALQT_LPARSER_H
#define GLOBALQT_LPARSER_H
#include <ldefines.h>
#include <lwidgets.h>
#include <lmain.h>
#include <widgets/lmodeditor.h>
#include <qzipreader_p.h>

#define ParserVer "0.1"

// Zips
struct LZipEntry {
	QString name, desc, devl, site, type, ver, rev, file;
	QJsonArray depn, ower;
	
	LZipEntry(){}
	LZipEntry(QJsonObject o, QString f);
	
	QString toString();
	bool    isValid();
};

struct LZipErr {
	LZipEntry entr;
	QString err;
	
	LZipErr(LZipEntry en, QString e): entr(en), err(e){}
	
	QString toString();
};
// Zips


// LParser
class LParser {
	QList<LZipEntry>* list;
	QList<LZipErr>* err;
	QStringList* coremods, *mods, *packs, *unknown;

	LZipEntry not_found;
	
public:
	LParser();
	
	void addE(LZipEntry e, QDir curr);
	void addToList(LZipEntry e);
	
	void parseZip();
	void unzipDownloads();
	void parse();
	void check();
	
	void showErr();
	
	void write();
	void writeT(QString type, QStringList* list);
	void clear();

	inline	QString getTDir(QString name);
	inline	QString getDir(QString type, QString name);
	inline LZipEntry search(QString n);
};
// LParser


// Standalone
QJsonObject loadJson(QString file);
void saveJson(QJsonObject o, QString file);
// Standalone

#endif // GLOBALQT_LPARSER
