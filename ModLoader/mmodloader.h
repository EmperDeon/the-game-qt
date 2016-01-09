#ifndef MODLOADER_H
#define MODLOADER_H

#include <QtCore>
#include <ModLoader/mdefines.h>
#include <ModLoader/mutils.h>
#include <ModLoader/core/mcoremods.h>
#include <ModLoader/mods/mmods.h>
#include "Engine/econtainers.h"

class MCoreMods;
class MMods;

class MModLoader : public QObject, IModLoader {
	Q_OBJECT
	Q_PLUGIN_METADATA(IID "org.ilzcorp.IModLoader" FILE "coremod.json")
	Q_INTERFACES(IModLoader)
 QString className = "M-ModLoader";

	MCoreMods* core;
	MMods* mods;

 MModLoader * loader;
public:
	IVars* vars;
	ILogger* log;

 QString getName() override;

	void setVars(IVars* v) override;
	void corePreInit() override;
	void coreInit() override;
	void corePostInit() override;

	void preInit() override;
	void init() override;
	void postInit() override;

private:

};

#endif // MODLOADER_H
