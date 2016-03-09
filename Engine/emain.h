#ifndef GLOBALQT_EMAIN_H
#define GLOBALQT_EMAIN_H
#include <idefines.h>
#include <QtWidgets>
#include <time.h>
#include <Engine/eutils.h>
#include <Engine/ewidgets.h>
#include <Engine/emods.h>
#include <ModLoader/core/render/mrender.h>

class ELogger;
class ESettings;
class EDeveloper;
class EVars;
class EMods;
class EMWidget;


class EMain : public IMain{
	Q_OBJECT

	QSplashScreen* splash;
	// Threads
	QThreadPool* queue;
	QThread* ren_t;
	
	EDeveloper * wdev;
	EMods * mods;
	
	MGlWidget* wgt;
	
public:
	EMain();
	virtual void setSplashLabel(QString);
	virtual QSplashScreen* getSplashSceen() {return splash;}
	        void init();
	        void show();
	        void destroy();
public slots:
	void lastWindowClosed(){destroy();}
};
 
void qtMessageHandler(QtMsgType type, const QMessageLogContext& cont, const QString& msg);

#endif //GLOBALQT_EMAIN
