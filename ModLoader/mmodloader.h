#ifndef MODLOADER_H
#define MODLOADER_H

#include <QtCore>
#include <ModLoader/mutils.h>
#include <Global/gmodinterfaces.h>
#include <Global/gcontainers.h>
#include <Launcher/lutils.h>
#include <ModLoader/mparser.h>
#include <ModLoader/mrender.h>

class LModsWidget;
class LModEditor;
class LPacker;
class MModsList;
class MParser;
class MRender;

class ModLoader : public QObject, GModLoaderInterface{
	Q_OBJECT
	Q_PLUGIN_METADATA(IID "org.ilzcorp.GModLoaderInterface" FILE "coremod.json")
	Q_INTERFACES(GModLoaderInterface)

	MParser *parser;
public:
	IVars* vars;
	ILogger* log;
	QList<QJsonObject>* jsons;

	MRender *render;

 QString getName() Q_DECL_OVERRIDE;
	// Engine
	void setVars(IVars* v) Q_DECL_OVERRIDE;
	void corePreInit() Q_DECL_OVERRIDE;
	void coreInit() Q_DECL_OVERRIDE;
	void corePostInit() Q_DECL_OVERRIDE;

	void preInit() Q_DECL_OVERRIDE;
	void init() Q_DECL_OVERRIDE;
	void postInit() Q_DECL_OVERRIDE;



};

#endif // MODLOADER_H
