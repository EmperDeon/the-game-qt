#ifndef G_MODINTERFACES
#define G_MODINTERFACES
#include <QString>
#include <../Launcher/lwidgets.h>

class LLogWidget;

class GModLoaderInterface{
public:
	virtual QString getName() = 0;
	virtual ~GModLoaderInterface() {}
	// Launcher
	virtual void parseZips() = 0;
	virtual void setLogger(LLogWidget* log) = 0;
	virtual void showMods() = 0;
	virtual void showModEditor() = 0;
	virtual void showPacker() = 0;
	// Engine
	virtual void corePreInit() = 0;
	virtual void coreInit() = 0;
	virtual void corePostInit() = 0;
	virtual void preInit() = 0;
	virtual void init() = 0;
	virtual void postInit() = 0;
};

QT_BEGIN_NAMESPACE

#define ModLoaderInterface_iid "org.ilzcorp.GModLoaderInterface"

Q_DECLARE_INTERFACE(GModLoaderInterface, ModLoaderInterface_iid)
QT_END_NAMESPACE

#endif

