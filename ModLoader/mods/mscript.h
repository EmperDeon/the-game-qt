#ifndef GLOBALQT_MSCRIPT_H
#define GLOBALQT_MSCRIPT_H
#include <ModLoader/mdefines.h>

class MScriptsContainer {
public:
	MScriptsContainer();

	void preInit();
	void init();
	void postInit();
};


#endif //GLOBALQT_MSCRIPT_H
