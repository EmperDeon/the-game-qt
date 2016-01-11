#ifndef GLOBALQT_EMODS_H
#define GLOBALQT_EMODS_H
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
