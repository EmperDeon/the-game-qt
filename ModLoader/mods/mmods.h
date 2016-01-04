#ifndef GLOBALQT_MMODS_H
#define GLOBALQT_MMODS_H

#include <ModLoader/mdefines.h>
#include <ModLoader/mmodloader.h>
#include <ModLoader/mods/mtext.h>
#include <ModLoader/mods/mscript.h>
#include <ModLoader/mods/mplugin.h>

#include <QtCore>
#include <ModLoader/core/level/mlevel.h>

class MModLoader;
class ILogger;
class IVars;

class MTextContainer;
class MScriptsContainer;
class MPluginsContainer;

class MMods{
 MModLoader * loader;
	QString className = "M-Mods";
	IMain* main;

	MTextContainer*    text;
	MScriptsContainer* script;
	MPluginsContainer* plugin;
public:
	ILogger* log;
	IVars* vars;

	MMods(MModLoader * l);

	void preInit();
	void init();
	void postInit();
};

#endif //GLOBALQT_MMODS_H
