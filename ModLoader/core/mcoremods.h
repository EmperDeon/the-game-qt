#ifndef GLOBALQT_MCOREMODS_H
#define GLOBALQT_MCOREMODS_H

#include <ModLoader/mdefines.h>
#include <ModLoader/mmodloader.h>
#include <ModLoader/core/mrender.h>
#include <ModLoader/core/mactions.h>
#include <ModLoader/mutils.h>

class ModLoader;
class ILogger;
class IVars;
class MRender;
class MActions;

class MCoreMods {
	QString className = "M-CoreMods";
	MRender *render;
	MActions* actions;

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
