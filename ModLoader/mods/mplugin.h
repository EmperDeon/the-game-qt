#ifndef GLOBALQT_MPLUGIN_H
#define GLOBALQT_MPLUGIN_H
#include <ModLoader/mmodloader.h>
#include <Global/gmodinterfaces.h>

class MMods;
class ILogger;
class IVars;

class MPluginsContainer {
	MMods* loader;
	ILogger* log;
	IVars* vars;

 QList<IMod*>* plugins;
public:
	MPluginsContainer(MMods *l);

	void preInit();
	void init();
	void postInit();
};


#endif //GLOBALQT_MPLUGIN_H
