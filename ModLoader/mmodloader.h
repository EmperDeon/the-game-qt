#ifndef MODLOADER_H
#define MODLOADER_H

#include <../ModLoader/mparser.h>
#include <../ModLoader/mutils.h>
#include <../ModLoader/mmodswidget.h>
#include <../Global/gmodinterfaces.h>
#include <../Launcher/lutils.h>

class Parser;
class MModsWidget;
class MModEditor;
class MPacker;
class MModsList;

class ModLoader : public QObject, GModLoaderInterface{
	Q_OBJECT
	Q_PLUGIN_METADATA(IID "org.ilzcorp.GModLoaderInterface" FILE "coremod.json")
	Q_INTERFACES(GModLoaderInterface)

public:
	LLogWidget* w_log;
	MModsList* modsMap;

	Parser* parser;
	MModsWidget* w_mod;
	MModEditor* w_mode;
	MPacker* w_pack;

//	ModLauncher();
	QString getName() Q_DECL_OVERRIDE;
	//Launcher
	void parseZips() Q_DECL_OVERRIDE;
	void setLogger(LLogWidget *log) Q_DECL_OVERRIDE;
	void showMods() Q_DECL_OVERRIDE;
	void showModEditor() Q_DECL_OVERRIDE;
	void showPacker() Q_DECL_OVERRIDE;
	// Engine
	void corePreInit() Q_DECL_OVERRIDE;
	void coreInit() Q_DECL_OVERRIDE;
	void corePostInit() Q_DECL_OVERRIDE;

	void preInit() Q_DECL_OVERRIDE;
	void init() Q_DECL_OVERRIDE;
	void postInit() Q_DECL_OVERRIDE;
};

#endif // MODLOADER_H
