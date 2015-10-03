#ifndef MODLOADER_H
#define MODLOADER_H

#include <QtCore>
#include <ModLoader/mutils.h>
#include <ModLoader/mparser.h>
#include <ModLoader/core/mrender.h>
#include <Global/gcontainers.h>
#include <Launcher/lutils.h>

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


 QMap<QString, Emiks*> map;
	MParser *parser;
public:
	IVars* vars;
	ILogger* log;
	QList<QJsonObject>* jsons;

	QList<IMod*>* lmods;
	QList<ICoreMod*>* lcmods;

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

private:
	void addModInstance(QJsonObject o);
	void addCoreModInstance(QJsonObject o);
	QObject* instance(QString f);
};

#endif // MODLOADER_H
