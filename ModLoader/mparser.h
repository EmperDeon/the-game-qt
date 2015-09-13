#ifndef PARSER_H
#define PARSER_H
#include <QtCore>
#include <QtGui/private/qzipreader_p.h>
#include <QtGui/private/qzipwriter_p.h>
#include <../Launcher/lwidgets.h>
#include <mmodloader.h>

class ModLoader;

struct ZipEntry{
	QString name;
	QString desc;
	QString devl;
	QString site;
	QString type;
	QJsonArray depn;
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

class Parser{
	QList<ZipEntry>* list;
	QList<ZipErr  >* err;

	QStringList* coremods;
	QStringList* mods;
	QStringList* packs;
	QStringList* unknown;

	ModLoader* loader;
	LLogWidget* log;
	bool needDep;
	ZipEntry not_found;
public:
	Parser(ModLoader* l);
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
	void makeList();

	ZipEntry search(QString n);
};

void createJson();
QJsonObject loadJson(QString file);
void saveJson(QJsonObject o, QString file);
#endif // PARSER_H
