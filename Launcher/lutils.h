#ifndef GLOBALQT_LUTILS_H
#define GLOBALQT_LUTILS_H
#include <Launcher/ldefines.h>
#include <Launcher/lmain.h>
#include <Launcher/qzipreader_p.h>
#include <Launcher/qzipwriter_p.h>

class LMainWindow;


// Logs
#define ESERVER_NAME "GameLogServer"
#define ELOG_DATE_FORMAT "HH:mm:ss" // "HH:mm:ss dd.MM.yyyy"

struct LLogE {
	ILogLevel lv;
	QDateTime d;
	QString t, cl, ms;
	bool engine;

	LLogE(ILogLevel lvl, QDateTime dt, QString cls, QString mss);
	LLogE(QString);

	QString parseQtFunc(QString s);
	QString toString();
};

class LLogWidget : public QWidget{
 Q_OBJECT

	ILogLevel curr;
	QString last;
	QList<LLogE>* list;
	QTextEdit* w_edit;
	QLabel* w_c;
 QCheckBox* c_qt;

public slots:
	void switchE() {switchL(ILogLevel::ERR);}
	void switchW() {switchL(ILogLevel::WARN);}
	void switchI() {switchL(ILogLevel::INFO);}
	void switchD() {switchL(ILogLevel::DEBUG);}
	void switchF() {switchL(ILogLevel::FINE);}
	void switchFF(){switchL(ILogLevel::FFINE);}
	void switchA() {switchL(ILogLevel::ALL);}

	void refresh();
public:
	LLogWidget();
	void log(ILogLevel lv, QString cl, QString m){addL(LLogE(lv, QDateTime::currentDateTime(), cl, m ));}
	void addL(LLogE e);
	void switchL(ILogLevel lv);
};
// Logs


// LLocalServer
class LLocalServer : public QObject{
	Q_OBJECT

	QString lastMsg;
	quint16 blockSize;
	QLocalServer *server;

	void addLog(QString s);

private slots:
	void newConnection();
	void readyRead();

public:
	QVector<QLocalSocket *>* clients;
	LLocalServer();
};
// LLocalServer


// LModsLost
class LModsList{
	LMainWindow* loader;
	QJsonArray* list;

	void update();
	void fillList();
	void addToList(QJsonObject);
	bool contains(QString);
	void disable(QString n);
public:
	QJsonArray lst;

	LModsList(LMainWindow*);
	void addNew();
	void load();
	void save();
	void reload();

};
// LModsList


// Standalone functions
QJsonObject loadJson(QString file);
QJsonArray  loadJsonA(QString file);
void        saveJson(QJsonObject o, QString file);
void        saveJsonA(QJsonArray o, QString file);
// Standalone functions

#endif // LUTILS_H
