#ifndef G_MODINTERFACES
#define G_MODINTERFACES
#include <QString>
#include <QtWidgets>

enum class GLogLevel;
class IVars;
class Emiks;

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

class IRender{
public:
	virtual void init() = 0;
	virtual void render(QPaintDevice* dev) = 0;
	virtual ~IRender(){};
};

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
	virtual void* get(QString name) = 0;
	virtual void set(void* o, QString n) = 0;
	virtual void setOverwriteList(QStringList l) = 0;
	virtual ~IVars(){};
};


class IModsIds {
public:
	virtual Emiks* get(QString m, QString i, QString k, int s) = 0;
	
};

#include <GLobal/gmain.h>
#include <Global/gutils.h>
#include <Global/gcontainers.h>

QT_BEGIN_NAMESPACE

Q_DECLARE_INTERFACE(GModLoaderInterface, "org.ilzcorp.GModLoaderInterface")
Q_DECLARE_INTERFACE(IRender, "org.ilzcorp.GRenderInterface")
Q_DECLARE_INTERFACE(IMain, "org.ilzcorp.IMain")
Q_DECLARE_INTERFACE(ILogger, "org.ilzcorp.ILogger")
Q_DECLARE_INTERFACE(IVars, "org.ilzcorp.IVars")

QT_END_NAMESPACE
#endif

