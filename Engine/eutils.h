#ifndef G_UTILS
#define G_UTILS

#include <QtCore>
#include <QtNetwork>
#include "Engine/edefines.h"

class ELogger : public QObject, public ILogger{
	Q_INTERFACES(ILogger)
 Q_OBJECT
	QString className = "E-Logger";
	QStringList lst;
	bool conn;
	QLocalSocket* socket;
private slots:
	void connected();
	void disc();
public:
	ELogger();
	void log(GLogLevel lv, QString cl, QString ms)  Q_DECL_OVERRIDE;
	void sendM(QString s)  Q_DECL_OVERRIDE;
	void connec();
};

class ESettings : public QObject{
	Q_OBJECT
	QString className = "E-Settings";
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
	Q_INTERFACES(IVars)
	QString className = "E-Vars";
	QMap<QString, void*>* map;
	QStringList* owlist;
public:
	EVars();
	bool contains(QString name)  Q_DECL_OVERRIDE;
	bool contains(QStringList l) Q_DECL_OVERRIDE;
	void* get(QString name)  Q_DECL_OVERRIDE;
	void set(void* o, QString n)  Q_DECL_OVERRIDE;
 void setOverwriteList(QStringList l)  Q_DECL_OVERRIDE;
};

QString getLevelName(GLogLevel lv);

#endif
