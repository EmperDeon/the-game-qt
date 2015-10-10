#ifndef GLOBALQT_MPLUGIN_H
#define GLOBALQT_MPLUGIN_H

#include <ModLoader/mdefines.h>
#include <ModLoader/mmodloader.h>
#include <Engine/emodinterfaces.h>

class MMods;
class ILogger;
class IVars;

class MPluginsContainer {
	MMods* loader;
	QString className = "M-PluginsContainer";
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
