#ifndef MODLOADER_H
#define MODLOADER_H

#include <QtCore>
#include <ModLoader/mutils.h>
#include <ModLoader/core/mcoremods.h>
#include <ModLoader/mods/mmods.h>
#include <Global/gcontainers.h>
#include <Launcher/lutils.h>

class MCoreMods;
class MMods;

class ModLoader : public QObject, GModLoaderInterface{
	Q_OBJECT
	Q_PLUGIN_METADATA(IID "org.ilzcorp.GModLoaderInterface" FILE "coremod.json")
	Q_INTERFACES(GModLoaderInterface)

	MCoreMods* core;
	MMods* mods;

public:
	IVars* vars;
	ILogger* log;

 QString getName() Q_DECL_OVERRIDE;
	// Engine
	void setVars(IVars* v) Q_DECL_OVERRIDE;
	void corePreInit() Q_DECL_OVERRIDE;
	void coreInit() Q_DECL_OVERRIDE;
	void corePostInit() Q_DECL_OVERRIDE;

	void preInit() Q_DECL_OVERRIDE;
	void init() Q_DECL_OVERRIDE;
	void postInit() Q_DECL_OVERRIDE;

private:

};

#endif // MODLOADER_H
