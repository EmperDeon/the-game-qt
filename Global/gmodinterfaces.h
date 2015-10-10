#ifndef G_MODINTERFACES
#define G_MODINTERFACES
#include <QString>
#include <QtWidgets>

enum class GLogLevel{ERR = 1, WARN = 2, INFO = 3, DEBUG = 4, FINE = 5, FFINE = 6, ALL = 7};
class IVars;
class Emiks;

//ModLoader

class GModLoaderInterface{
public:
	virtual QString getName() = 0;
	virtual ~GModLoaderInterface() {}
	// Engine
	virtual void setVars(IVars* v) = 0;
	virtual void corePreInit() = 0;
	virtual void coreInit() = 0;
	virtual void corePostInit() = 0;
	virtual void preInit() = 0;
	virtual void init() = 0;
	virtual void postInit() = 0;

};
class IModsIds {
public:
	virtual Emiks* get(QString m, QString i, QString k, int s) = 0;
};

class IItem{
public:
	virtual float getStackSize() = 0;
	virtual int getStackType() = 0;
};
class IItemsContainer{
public:
	virtual IItem* get(Emiks* id) = 0;
 virtual Emiks* get(IItem* it) = 0;
};

class IBlock{
public:
	virtual float getWeight() = 0;
};
class IBlocksContainer{
public:
	virtual IBlock* get(Emiks* id) = 0;
	virtual Emiks* get(IBlock* id) = 0;
};

class ITool{
public:
	virtual QString getType() = 0;
	virtual int getDurability() = 0;
};
class IToolsContainer{
public:
	virtual ITool* get(Emiks* id) = 0;
	virtual Emiks* get(ITool* id) = 0;
};
//!ModLoader
//CoreMods

class ICoreMod{
public:
	virtual QStringList getOwList() = 0;
	virtual QStringList getDpList() = 0;

	virtual void setVars(IVars* v) = 0;
	virtual void preInit() = 0;
	virtual void init() = 0;
	virtual void postInit() = 0;
};
class IRender{
public:
	virtual void init() = 0;
	virtual void render(QPaintDevice* dev) = 0;
	virtual ~IRender(){};
};

//!CoreMods
//Mods

class IMod{
public:
	virtual QStringList getOwList() = 0;
	virtual QStringList getDpList() = 0;

	virtual void setVars(IVars* v) = 0;
	virtual void preInit() = 0;
	virtual void init() = 0;
	virtual void postInit() = 0;
};

//!Mods
//Engine

class IMain{
public:
	virtual void init() = 0;
	virtual void show() = 0;
	virtual void destroy() = 0;
	virtual ~IMain(){};
};
class ILogger{
public:
	virtual void log(GLogLevel lv, QString cl, QString ms) = 0;
	virtual void sendM(QString s) = 0;
	virtual ~ILogger(){};
};
class IVars{
public:
	virtual bool contains(QString name) = 0;
	virtual bool contains(QStringList l) = 0;
	virtual void* get(QString name) = 0;
	virtual void set(void* o, QString n) = 0;
	virtual void setOverwriteList(QStringList l) = 0;
	virtual ~IVars(){};
};

//!Engine

#include <GLobal/gmain.h>
#include <Global/gcontainers.h>

QT_BEGIN_NAMESPACE
// ModLoader
Q_DECLARE_INTERFACE(GModLoaderInterface, "org.ilzcorp.GModLoaderInterface")
Q_DECLARE_INTERFACE(IModsIds, "org.ilzcorp.IModsIds")

Q_DECLARE_INTERFACE(IItemsContainer, "org.ilzcorp.IItemsContainer")
Q_DECLARE_INTERFACE(IItem, "org.ilzcorp.IItem")

Q_DECLARE_INTERFACE(IBlocksContainer, "org.ilzcorp.IBlocksContainer")
Q_DECLARE_INTERFACE(IBlock, "org.ilzcorp.IBlock")

//!ModLoader
//CoreMod

Q_DECLARE_INTERFACE(ICoreMod, "org.ilzcorp.ICoreMod")
Q_DECLARE_INTERFACE(IRender,  "org.ilzcorp.GRenderInterface")

//!CoreMod
//Mod

Q_DECLARE_INTERFACE(IMod,     "org.ilzcorp.IMod")

//!Mod
//Engine

Q_DECLARE_INTERFACE(IMain,    "org.ilzcorp.IMain")
Q_DECLARE_INTERFACE(ILogger,  "org.ilzcorp.ILogger")
Q_DECLARE_INTERFACE(IVars,    "org.ilzcorp.IVars")

//!Engine
// Q_DECLARE_INTERFACE(, "org.ilzcorp.")
QT_END_NAMESPACE
#endif

