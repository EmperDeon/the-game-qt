#ifndef PARSER_H
#define PARSER_H

#include <QtCore>
#include <Launcher/lwidgets.h>
#include <Launcher/lmain.h>
#include <Launcher/qzipreader_p.h>

class LLogWidget;
class LMainWindow;

struct ZipEntry{
	QString name;
	QString desc;
	QString devl;
	QString site;
	QString type;
	QJsonArray depn;
	QJsonArray ower;
	QString ver;
	QString rev;
	QString file;
	ZipEntry(){}
	ZipEntry(QJsonObject o, QString f);
	QString toString();
//	void write(QJsonArray& a);
	bool isValid();
};
struct ZipErr{
	ZipEntry entr;
	QString err;
	ZipErr(ZipEntry en, QString e):entr(en), err(e){}
	QString toString();
};

class LParser {
	QList<ZipEntry>* list;
	QList<ZipErr  >* err;

	QStringList* coremods;
	QStringList* mods;
	QStringList* packs;
	QStringList* unknown;

	LLogWidget* log;
	bool needDep;
	ZipEntry not_found;
public:
	LParser(LMainWindow* l);
	void addE(ZipEntry e, QDir curr);
	void addToList(ZipEntry e);
	void parseZip();
	void unzipDownloads();
	void parse();
	void check();
	void showErr();
	inline	QString getTDir(QString name);
	inline	QString getDir(QString type, QString name);
	void write();
	void writeT(QString type, QStringList* list);
	void clear();

	ZipEntry search(QString n);
};

QJsonObject loadJson(QString file);
void saveJson(QJsonObject o, QString file);
#endif // PARSER_H
