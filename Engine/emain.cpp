#include <time.h>
#include "Engine/emain.h"

int main(int argc, char *argv[]){
	QApplication a(argc, argv);
	QCoreApplication::setOrganizationName("IlzSoft");
	QCoreApplication::setOrganizationDomain("github.com/ilz2010");
	QCoreApplication::setApplicationName("The game");

	GV_LOGGER = new ELogger;
	GV_VARS = new EVars;

 EMain * gMain = new EMain();
	gMain->init();
 gMain->show();

	return a.exec();
}

EMain::EMain() {
 srand(unsigned(int(time(NULL))));

	splash = new QSplashScreen(QPixmap("splash.png").scaledToHeight(500));
	//splash->show();

 varS(this, "eMain");
	varS(GV_LOGGER, "eLogger");

	mods = new EMods();

	varS(wgt, "eMainWindow");
	varS(wdev, "eDev");
	varS(mods, "eMods");
}

void EMain::init() {
	mods->coreInit();

//	wgt = new EMWidget();
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
