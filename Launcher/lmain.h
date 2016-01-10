#ifndef GLOBALQT_LMAIN
#define GLOBALQT_LMAIN
#include <Launcher/ldefines.h>
#include <Launcher/lutils.h>
#include <Launcher/lwidgets.h>
#include <Launcher/lparser.h>


class LDevelop;
class LLocalServer;
class LModLoaderSelect;
class IModLoader;
class LLogWidget;
class LModsList;
class LParser;

// Widgets
class LMainWindow : public QMainWindow{
	Q_OBJECT

	QString dir;
	QString site;
	QString rfile;
	QProcess* proc;
	bool devvis;

	LLocalServer * srv;

	QWidget* wgt;

	QPushButton* bstart;
	QPushButton* bdev;
	QLineEdit* elog;
	QLineEdit* epas;

	QCheckBox* log;
	QListView* list;
	QProgressBar* prog;

public:
	LDevelop * dev;
	LModsList * modsMap;
	LParser * parser;

	LMainWindow();

private:
	void initNews();
	void initLog();
	void collectWidgets();

	void check();
	void checkSettings();
	void checkDir();

	void parse();

	void download();

protected:
	void closeEvent(QCloseEvent *event);

public slots:
	void showDev();
	void launch();
	void procF(int e);
};

#endif //GLOBALQT_LMAIN
