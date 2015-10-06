#ifndef GLOBALQT_MCOREMODS_H
#define GLOBALQT_MCOREMODS_H
#include <ModLoader/mmodloader.h>
#include <ModLoader/core/mrender.h>

class ModLoader;
class ILogger;
class IVars;
class MRender;

class MCoreMods {
	MRender *render;
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
