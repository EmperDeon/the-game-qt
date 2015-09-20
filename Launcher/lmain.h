#ifndef H_MAIN
#define H_MAIN
#include <QApplication>
#include <Launcher/lutils.h>
#include <Launcher/lwidgets.h>
#include <Global/gmodinterfaces.h>

#define CLASS_NAME "Not_Defined"

class GDevelop;
class MLocalServer;
class GModLoaderSelect;
class GModLoaderInterface;
class LLogWidget;

// Widgets
class LMainWindow : public QMainWindow{
	Q_OBJECT
	QString dir;
	QString site;
	QString rfile;
	QProcess* proc;
	GDevelop* dev;
	bool devvis;

	MLocalServer* srv;
	QString lastMsg;

	QString jQuery;
	QWebView *view;
	QLineEdit *locationEdit;
	QWidget* wgt;

	QHBoxLayout* layout;
	QVBoxLayout* vlay;
	QHBoxLayout* hlay;
	QGridLayout* slay;
	QGridLayout* llay;
	QSpacerItem* spac;

	QPushButton* bstart;
	QPushButton* bdev;
	QLineEdit* elog;
	QLineEdit* epas;

	QCheckBox* log;
	QListView* list;
	QProgressBar* prog;

	int progress;

	GModLoaderInterface* modloader;
	QMap<QString, QString>* modloaderlist;

	QTableView* selectmodv;
	GModLoaderSelect* selectmodl;
public:
	LLogWidget* w_log;
	LMainWindow();
	GModLoaderInterface* getModLoader();
	void initModLoaders();
public slots:
	void showDev();
	void launch();
	void procF(int e);
private:
	void initWebKit();
	void initLog();
	void collectWidgets();

	void check();
	void checkSettings();
	void checkDir();

	void initModLoaderList();
	void loadModLoader(QString s);
	void selectModLoader();
	void parse();

	void download();
protected slots:
	void adjustLocation();
	void changeLocation();
	void adjustTitle();
	void setProgress(int p);
	void finishLoading(bool);
protected:
	void closeEvent(QCloseEvent *event);
};

#endif
