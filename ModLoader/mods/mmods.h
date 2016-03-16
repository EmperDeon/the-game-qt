#ifndef GLOBALQT_MMODS_H
#define GLOBALQT_MMODS_H
#include <idefines.h>
#include <mods/mtext.h>
#include <mods/mscript.h>
#include <mods/mplugin.h>


class MTextContainer;
class MScriptsContainer;
class MPluginsContainer;

class MMods{
	IMain* main;

public:
	MTextContainer*    text;
	MScriptsContainer* script;
	MPluginsContainer* plugin;

	MMods();

	void preInit();
	void init();
	void postInit();
};

#endif //GLOBALQT_MMODS_H
