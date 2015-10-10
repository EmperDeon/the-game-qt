#ifndef G_MODS
#define G_MODS

#include <QtCore>
#include "Engine/edefines.h"

class IModLoader;

class EMods : public QObject {
	Q_OBJECT
	QString className = "E-Mods";
	IModLoader * modloader;
	QMap<QString, QString>* modloaderlist;
private:
	void initModLoaders();
public:
	EMods();
	void coreInit();
	void init();

};

#endif
