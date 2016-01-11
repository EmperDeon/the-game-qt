#ifndef GLOBALQT_EMAIN_H
#define GLOBALQT_EMAIN_H
#include <Engine/edefines.h>
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
	
	        void init();
	        void show();
	        void destroy();
};
 

#endif //GLOBALQT_EMAIN
