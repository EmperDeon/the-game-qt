#ifndef GLOBALQT_MCOREMODS_H
#define GLOBALQT_MCOREMODS_H
#include <ModLoader/mdefines.h>
#include <ModLoader/core/level/mlevel.h>
#include <ModLoader/core/level/mchunk.h>
#include <ModLoader/core/render/perf/mperfw.h>
#include <ModLoader/core/render/mrender.h>
#include <ModLoader/core/mactions.h>
#include <ModLoader/mutils.h>

class MGlWidget;
class MActions;
class MLevelManager;
class MPerfomanceWidget;

class MCoreMods {
	IMain* main;
 QThread* t_ren;

	MPerfomanceWidget* perf;
	MActions* actions;
 MLevelManager* level;

 QList<ICoreMod*>* plugins;

public:
	QThreadPool* queue;
	MGlWidget *render;

	MCoreMods();

	void parseOwerwrites();
	void loadPlugins();
	void preInit();

	void init();

	void postInit();
};


#endif //GLOBALQT_MCOREMODS_H
