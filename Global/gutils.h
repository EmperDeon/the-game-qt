#ifndef G_UTILS
#define G_UTILS

#include <QtCore>
#include <QtNetwork>
#include <../Global/gmain.h>

class Utils{
public:
	Utils();
};

enum class GLogLevel{
	ERR = 1, WARN = 2, INFO = 3, DEBUG = 4, FINE = 5, FFINE = 6, ALL = 7
};

class GLogger : public QObject{
	Q_OBJECT

	QStringList lst;
	bool conn;
	QLocalSocket* socket;
private slots:
	void connected();
	void disc();
public:
	GLogger();
	void log(GLogLevel lv, QString cl, QString ms);
	void sendM(QString s);
	void connec();
	void discon();
};

class GSettings : public QObject{
	Q_OBJECT

	QMap<QString, QJsonObject> map;
	QString file;

public:
	GSettings(QString f);
	~GSettings();
	QJsonObject& operator[] (QString k);
	QJsonObject& get(QString n);
	void addNewCategory(QString n);
	void save();
	void load();
	void loadFrom(QString f);
	void saveTo(QString f);
};

class GVars : public QObject{
	Q_OBJECT
	QMap<QString, QObject*>* map;
public:
	GVars();
	bool contains(QString name);
	QObject* get(QString name);
	void set(QObject* o, QString n);

};

QString getLevelName(GLogLevel lv);

#endif
