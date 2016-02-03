#ifndef GLOBALQT_EUTILS_H
#define GLOBALQT_EUTILS_H
#include <Engine/edefines.h>
#include <QtNetwork>

// ELogger
#define ESERVER_NAME "GameLogServer"
#define ELOG_DATE_FORMAT "HH:mm:ss" // "HH:mm:ss dd.MM.yyyy"

QString getLevelName(ILogLevel lv);

class ELogger : public QObject, public ILogger{
 Q_OBJECT

	QStringList lst;
	QLocalSocket* socket;

	bool conn;

private slots:
	void connected();
	void disc();

public:
	ELogger();

	virtual void log(ILogLevel lv, QString, QString)  override;
	virtual void sendM(QString)                       override;
};
// ELogger


// ESettings
class ESettings : public ISettings{
	QMap<QString, QJsonObject> map;
	QString file;

public:
	ESettings(QString f);
	~ESettings();

	virtual QJsonObject& operator[] (QString) override;
	virtual QJsonObject& get(QString)         override;

	virtual void addNewCategory(QString)      override;

	virtual void save()                       override;
	virtual void load()                       override;
	virtual void loadFrom(QString)            override;
	virtual void saveTo(QString)              override;
};

class ESettCont : public ISettCont {
	QMap<QString, ISettings*>* map;
public:
	ESettCont();

	virtual ISettings* getSettings(QString) override;

};
// ESettings


// EVars
class EVars : public IVars{
	QMap<QString, void*>* map;
	QStringList* owlist;

public:
	EVars();

	bool  contains(QString)              override;
	bool  contains(QStringList)          override;

	void* get(QString)                   override;

	void  set(void* o, QString)          override;
 void  setOverwriteList(QStringList)  override;
};
// EVars


// EDirs
class EDirs : public IDirs{
	QMap<QString, QString>* dirs;

public:
	EDirs();
	virtual void    addDir(QString, QString)   override;

	virtual QDir*   getDir(QString)            override;
	virtual QFile*  getFile(QString, QString)  override;

	virtual QString getSDir(QString)           override;
	virtual QString getSFile(QString, QString) override;
};
// EDirs

#endif //GLOBALQT_EUTILS
