#include <emain.h>


// Main
int main(int argc, char *argv[]){
	system( "copy ..\\GameTmp\\libE_MODLOADER.dll modLoader.dll /Y");
	system("xcopy ..\\GameTmp\\mods mods\\ /Y /E");

 qInstallMessageHandler(qtMessageHandler);
	QApplication a(argc, argv);
	a.setWindowIcon(QIcon(QPixmap("res/icon_e.png")));
	QCoreApplication::setOrganizationName("IlzSoft");
	QCoreApplication::setOrganizationDomain("github.com/ilz2010");
	QCoreApplication::setApplicationName("The game");

	IV_LOGGER = new ELogger;
	IV_VARS = new EVars;
	IV_DIRS = new EDirs;
 IV_SETC = new ESettCont;
	IV_SETT = IV_SETC->getSettings("settings.dat");
 IV_SETT->load();

 EMain* gMain = new EMain();
	QObject::connect(&a, SIGNAL(lastWindowClosed()), gMain, SLOT(lastWindowClosed()));
	return a.exec();
}
// Main


// EMain
EMain::EMain() {
 srand(unsigned(int(time(NULL))));

	splash = new QSplashScreen(QPixmap("res/splash.png").scaledToHeight(350));
	splash->show();

 this->ren_t = new QThread;
	this->queue = new QThreadPool;
	this->queue->setMaxThreadCount(1);

 varS(ren_t, "eRenderThread");
	varS(queue, "eThreadQueue");
	
 varS(this, "eMain");
	varS(IV_VARS, "eVars");
	varS(IV_LOGGER, "eLogger");
 varS(IV_SETT, "eSettings");
	varS(IV_SETC, "eSettCont");

	mods = new EMods();

	varS(wdev, "eDev");
	varS(mods, "eMods");

	logF("EMain constructed");
}

void EMain::init() {
	logF("Init started");

	mods->coreInit();

	wgt = varG(IGlWidget*, "mRender");
	wdev = new EDeveloper();
 mods->init();

	splash->finish(wgt);

	this->show();
	logF("Init finished");
}

void EMain::show() {
	logF("Showing widgets");
	wgt->showMaximized();
}

void EMain::destroy() {
	logF("Destroying started");
 IV_SETT->save();
	logF("Destroying finished");
}

void EMain::setSplashLabel(QString s) {
 this->splash->showMessage(s, Qt::AlignHCenter | Qt::AlignTop, Qt::white);
	qApp->processEvents();
}
// EMain
void qtMessageHandler(QtMsgType type, const QMessageLogContext& cont, const QString& msg) {
 switch(type){
	 case QtDebugMsg:    IV_LOGGER->log(ILogLevel::QT, "E-QtD", msg); break;
	 case QtWarningMsg:  IV_LOGGER->log(ILogLevel::QT, "E-QtW", msg); break;
	 case QtCriticalMsg: IV_LOGGER->log(ILogLevel::QT, "E-QtC", msg); break;
	 case QtFatalMsg:    IV_LOGGER->log(ILogLevel::QT, "E-QtF", msg); break;
 }
}
