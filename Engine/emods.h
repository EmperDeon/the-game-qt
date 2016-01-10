#ifndef GLOBALQT_EMODS
#define GLOBALQT_EMODS
#include <Engine/edefines.h>

class IModLoader;

class EMods{
	IModLoader * modloader;
	QMap<QString, QString>* modloaderlist;

	void initModLoaders();

public:
	EMods();

	void coreInit();
	void init();
};

#endif //GLOBALQT_EMODS
