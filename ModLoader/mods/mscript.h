#ifndef GLOBALQT_MSCRIPT_H
#define GLOBALQT_MSCRIPT_H

#include <ModLoader/mdefines.h>
#include <ModLoader/mmodloader.h>

class MMods;
class ILogger;
class IVars;

class MScriptsContainer {
	MMods* loader;
	QString className = "M-ScriptsContainer";
	ILogger* log;
	IVars* vars;

public:
	MScriptsContainer(MMods *l);

	void preInit();
	void init();
	void postInit();
};


#endif //GLOBALQT_MSCRIPT_H
