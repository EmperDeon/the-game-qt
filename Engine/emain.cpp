#include <Engine/emain.h>


// Main
int main(int argc, char *argv[]){
 qInstallMessageHandler(qtMessageHandler);
	QApplication a(argc, argv);
	a.setWindowIcon(QIcon(QPixmap("res/icon_e.png")));
	QCoreApplication::setOrganizationName("IlzSoft");
	QCoreApplication::setOrganizationDomain("github.com/ilz2010");
	QCoreApplication::setApplicationName("The game");

	EV_LOGGER = new ELogger;
	EV_VARS = new EVars;
 EV_SETC = new ESettCont;
	EV_SETT = EV_SETC->getSettings("settings.dat");
 EV_SETT->load();

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
	varS(EV_VARS, "eVars");
	varS(EV_LOGGER, "eLogger");
 varS(EV_SETT, "eSettings");
	varS(EV_SETC, "eSettCont");

	mods = new EMods();

	varS(wdev, "eDev");
	varS(mods, "eMods");
}

void EMain::init() {
	mods->coreInit();

	wgt = varG(MGlWidget*, "mRender");
	wdev = new EDeveloper();

 mods->init();

	splash->finish(wgt);

	this->show();
}

void EMain::show() {
	wgt->showMaximized();
}

void EMain::destroy() {
 EV_SETT->save();
}

void EMain::setSplashLabel(QString s) {
 this->splash->showMessage(s, Qt::AlignHCenter | Qt::AlignTop, Qt::white);
	qApp->processEvents();
}
// EMain
void qtMessageHandler(QtMsgType type, const QMessageLogContext& cont, const QString& msg) {
 switch(type){
	 case QtDebugMsg:    EV_LOGGER->log(ILogLevel::QT, "E-QtD", msg); break;
	 case QtWarningMsg:  EV_LOGGER->log(ILogLevel::QT, "E-QtW", msg); break;
	 case QtCriticalMsg: EV_LOGGER->log(ILogLevel::QT, "E-QtC", msg); break;
	 case QtFatalMsg:    EV_LOGGER->log(ILogLevel::QT, "E-QtF", msg); break;
 }
}
