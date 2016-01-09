#ifndef G_UTILS
#define G_UTILS

#include <QtCore>
#include <QtNetwork>
#include "Engine/edefines.h"

class ELogger : public QObject, public ILogger{
 Q_OBJECT
	QStringList lst;
	bool conn;
	QLocalSocket* socket;
private slots:
	void connected();
	void disc();
public:
	ELogger();
	void log(ILogLevel lv, QString cl, QString ms)  override;
	void sendM(QString s)  override;
	void connec();
};

class ESettings : public QObject{
	Q_OBJECT
	QMap<QString, QJsonObject> map;
	QString file;

public:
	ESettings(QString f);
	~ESettings();
	QJsonObject& operator[] (QString k);
	QJsonObject& get(QString n);
	void addNewCategory(QString n);
	void save();
	void load();
	void loadFrom(QString f);
	void saveTo(QString f);
};

class EVars : public IVars{
	QMap<QString, void*>* map;
	QStringList* owlist;
public:
	EVars();
	bool contains(QString name)  override;
	bool contains(QStringList l) override;
	void* get(QString name)  override;
	void set(void* o, QString n)  override;
 void setOverwriteList(QStringList l)  override;
};

class EDirs : public IDirs{
	QMap<QString, QString>* dirs;

public:
	EDirs();
	virtual void addDir(QString k, QString v) override;

	virtual QDir *getDir(QString k) override;
	virtual QFile *getFile(QString k, QString f) override;

	virtual QString getSDir(QString k) override;
	virtual QString getSFile(QString k, QString f) override;
};

QString getLevelName(ILogLevel lv);

#endif
