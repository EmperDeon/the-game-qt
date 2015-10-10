#ifndef GLOBALQT_MTEXT_H
#define GLOBALQT_MTEXT_H

#include <ModLoader/mdefines.h>
#include <ModLoader/mmodloader.h>

class MMods;
class ILogger;
class IVars;

class MTextContainer {
 MMods* loader;
	QString className = "M-TextContainer";
	ILogger* log;
	IVars* vars;

public:
	MTextContainer(MMods* l);

	void preInit();

	void init();

	void postInit();
};

#endif //GLOBALQT_MTEXT_H
