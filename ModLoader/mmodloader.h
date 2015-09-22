#ifndef MODLOADER_H
#define MODLOADER_H

#include <ModLoader/mutils.h>
#include <Global/gmodinterfaces.h>
#include <Launcher/lutils.h>

class LParser;
class LModsWidget;
class LModEditor;
class LPacker;
class MModsList;

class ModLoader : public QObject, GModLoaderInterface{
	Q_OBJECT
	Q_PLUGIN_METADATA(IID "org.ilzcorp.GModLoaderInterface" FILE "coremod.json")
	Q_INTERFACES(GModLoaderInterface)

public:
	GVars* vars;
	GLogger* log;

 QString getName() Q_DECL_OVERRIDE;
	// Engine
	void setVars(GVars* v) Q_DECL_OVERRIDE;
	void corePreInit() Q_DECL_OVERRIDE;
	void coreInit() Q_DECL_OVERRIDE;
	void corePostInit() Q_DECL_OVERRIDE;

	void preInit() Q_DECL_OVERRIDE;
	void init() Q_DECL_OVERRIDE;
	void postInit() Q_DECL_OVERRIDE;
};

#endif // MODLOADER_H
