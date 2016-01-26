#include <Engine/emain.h>


// Main
int main(int argc, char *argv[]){
 qInstallMessageHandler(qtMessageHandler);
	QApplication a(argc, argv);
	QCoreApplication::setOrganizationName("IlzSoft");
	QCoreApplication::setOrganizationDomain("github.com/ilz2010");
	QCoreApplication::setApplicationName("The game");

	GV_LOGGER = new ELogger;
	GV_VARS = new EVars;

 EMain* gMain = new EMain();
	gMain->init();
 gMain->show();

	return a.exec();
}
// Main


// EMain
EMain::EMain() {
 srand(unsigned(int(time(NULL))));

	splash = new QSplashScreen(QPixmap("splash.png").scaledToHeight(350));
	splash->show();

 this->ren_t = new QThread;
	this->queue = new QThreadPool;
	this->queue->setMaxThreadCount(1);

 varS(ren_t, "eRenderThread");
	varS(queue, "eThreadQueue");
	
 varS(this, "eMain");
	varS(GV_LOGGER, "eLogger");

	mods = new EMods();

	varS(wgt, "eMainWindow");
	varS(wdev, "eDev");
	varS(mods, "eMods");
}

void EMain::init() {
	mods->coreInit();

	wgt = varG(MGlWidget*, "mRender");
	wdev = new EDeveloper();

 mods->init();

	splash->finish(wgt);
}

void EMain::show() {
	//wdev->show();
	wgt->showMaximized();
}

void EMain::destroy() {

}

void EMain::setSplashLabel(QString s) {
 this->splash->showMessage(s, Qt::AlignHCenter | Qt::AlignTop, Qt::white);
	qApp->processEvents();
}
// EMain
void qtMessageHandler(QtMsgType type, const QMessageLogContext& cont, const QString& msg) {
 switch(type){
	 case QtDebugMsg:    GV_LOGGER->log(ILogLevel::QT, "Qt", msg); break;
	 case QtWarningMsg:  GV_LOGGER->log(ILogLevel::QT, "Qt", msg); break;
	 case QtCriticalMsg: GV_LOGGER->log(ILogLevel::QT, "Qt", msg); break;
	 case QtFatalMsg:    GV_LOGGER->log(ILogLevel::QT, "Qt", msg); break;
 }
}
