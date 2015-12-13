#ifndef GLOBALQT_MCOREMODS_H
#define GLOBALQT_MCOREMODS_H

#include <ModLoader/mdefines.h>
#include <ModLoader/mmodloader.h>
#include <ModLoader/core/level/mchunk.h>
#include <ModLoader/core/render/mrender.h>
#include <ModLoader/core/level/mlevel.h>
#include <ModLoader/core/mactions.h>
#include <ModLoader/mutils.h>

class ModLoader;
class ILogger;
class IVars;
class MGlWidget;
class MActions;
class MLevelManager;

class MCoreMods {
	QString className = "M-CoreMods";
	IMain* main;

	MGlWidget *render;
	MActions* actions;
 MLevelManager* level;

 QList<ICoreMod*>* plugins;

public:
	ModLoader* loader;
	ILogger* log;
	IVars* vars;

	MCoreMods(ModLoader* l);

	void parseOwerwrites();
	void loadPlugins();
	void preInit();

	void init();

	void postInit();
};


#endif //GLOBALQT_MCOREMODS_H
