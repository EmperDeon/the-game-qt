#ifndef G_UTILS
#define G_UTILS

#include <QtCore>
#include <QtNetwork>
#include <Global/gmodinterfaces.h>

class GLogger : public QObject, public ILogger{
	Q_INTERFACES(ILogger)
 Q_OBJECT

	QStringList lst;
	bool conn;
	QLocalSocket* socket;
private slots:
	void connected();
	void disc();
public:
	GLogger();
	void log(GLogLevel lv, QString cl, QString ms)  Q_DECL_OVERRIDE;
	void sendM(QString s)  Q_DECL_OVERRIDE;
	void connec();
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

class GVars : public IVars{
	Q_INTERFACES(IVars)

	QMap<QString, void*>* map;
	QStringList* owlist;
public:
	GVars();
	bool contains(QString name)  Q_DECL_OVERRIDE;
	bool contains(QStringList l) Q_DECL_OVERRIDE;
	void* get(QString name)  Q_DECL_OVERRIDE;
	void set(void* o, QString n)  Q_DECL_OVERRIDE;
 void setOverwriteList(QStringList l)  Q_DECL_OVERRIDE;
};

QString getLevelName(GLogLevel lv);

#endif
