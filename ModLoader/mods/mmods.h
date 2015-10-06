#ifndef GLOBALQT_MMODS_H
#define GLOBALQT_MMODS_H
#include <ModLoader/mmodloader.h>
#include <ModLoader/mods/mtext.h>
#include <ModLoader/mods/mscript.h>
#include <ModLoader/mods/mplugin.h>

class ModLoader;
class ILogger;
class IVars;

class MTextContainer;
class MScriptsContainer;
class MPluginsContainer;

class MMods{
 ModLoader* loader;

	MTextContainer*    text;
	MScriptsContainer* script;
	MPluginsContainer* plugin;
public:
	ILogger* log;
	IVars* vars;

	MMods(ModLoader* l);

	void preInit();
	void init();
	void postInit();
};

#endif //GLOBALQT_MMODS_H
