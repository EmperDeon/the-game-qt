#ifndef LUTILS_H
#define LUTILS_H

#include <QtCore>
#include <QtWidgets>
#include <QtNetwork>
#include <Launcher/lwidgets.h>
#include <Launcher/lmain.h>
#include <Launcher/qzipreader_p.h>
#include <Launcher/qzipwriter_p.h>

class LLogWidget;
class LMainWindow;
enum class GLogLevel{ERR = 1, WARN = 2, INFO = 3, DEBUG = 4, FINE = 5, FFINE = 6, ALL = 7};

struct LLogE {
	GLogLevel lv;
	QDateTime d;
	QString t;
	QString cl;
	QString ms;
	bool engine;
	LLogE(GLogLevel lvl,QDateTime dt, QString cls, QString mss);
	LLogE(QString);
	QString toString();
};

class GModLoaderSelect :public QAbstractTableModel{
private:
	QMap<QString, QString>& mp;
public:
	GModLoaderSelect(QMap<QString, QString>& m , QObject *pobj = 0);

	QVariant data(const QModelIndex& index, int nRole) const;
	int rowCount(const QModelIndex&) const;
	int columnCount(const QModelIndex&) const;
	Qt::ItemFlags flags(const QModelIndex& index)const;
};
class LSettingsModel :public QAbstractTableModel{
private:
	QString cat;
	QMap<QString, QJsonObject>& mp;
	QStringList ind;
public:
	LSettingsModel(QString c, QMap<QString, QJsonObject>& m , QObject *pobj = 0);

	QVariant data(const QModelIndex& index, int nRole) const;
	bool setData(const QModelIndex& index,const QVariant& value, int nRole );
	int rowCount(const QModelIndex&) const;
	int columnCount(const QModelIndex&) const;
	Qt::ItemFlags flags(const QModelIndex& index)const;
};
class LListModel : public QAbstractListModel{
private:
	QJsonArray obj;
public:
	LListModel(const QJsonArray &o, QObject* pobj = 0);
	QVariant data(const QModelIndex& index, int nRole) const;
	bool setData(const QModelIndex& index, const QVariant& value, int nRole);
	int rowCount(const QModelIndex& = QModelIndex()) const;
	QVariant headerData(int nSection, Qt::Orientation orientation, int nRole = Qt::DisplayRole) const;
	Qt::ItemFlags flags(const QModelIndex &index) const;
	void add(QString k);
	void del(QListView *i);
};
class LTableModel :public QAbstractTableModel{
private:
	QJsonObject& obj;
public:
	LTableModel(QJsonObject& o, QObject *pobj = 0);
	QVariant data(const QModelIndex& index, int nRole) const;
	bool setData(const QModelIndex& index,const QVariant& value, int nRole );
	int rowCount(const QModelIndex&) const;
	int columnCount(const QModelIndex&) const;
	Qt::ItemFlags flags(const QModelIndex& index)const;
	void add(QString k, QString v);
	void del(QString k);
};

class MLocalServer : public QObject{
	Q_OBJECT

	LLogWidget* log;
	QString lastMsg;
	quint16 blockSize;
	QLocalServer *server;

private:
	void addLog(QString s);
private slots:
	void newConnection();
	void readyRead();
public:
	QVector<QLocalSocket *> *clients;
	MLocalServer(LLogWidget* l);
};

void createJson();
QJsonObject loadJson(QFile file);
QJsonArray loadJsonA(QFile file);
QJsonObject loadJson(QString file);
QJsonArray loadJsonA(QString file);
void saveJson(QJsonObject o, QString file);
void saveJsonA(QJsonArray o, QString file);

QStringList getPluginFilter();

class MModsList : public QObject{
Q_OBJECT

	LMainWindow* loader;
	QJsonArray* list;

	void update();
	void fillList();
	void addToList(QJsonObject);
	bool contains(QString);
	void disable(QString n);
public:
	QJsonArray lst;

	MModsList(LMainWindow*);
	void addNew();
	void load();
	void save();
	void reload();

};

#endif // LUTILS_H
