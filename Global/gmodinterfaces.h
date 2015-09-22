#ifndef G_MODINTERFACES
#define G_MODINTERFACES
#include <QString>
#include <GLobal/gmain.h>

class GModLoaderInterface{
public:
	virtual QString getName() = 0;
	virtual ~GModLoaderInterface() {}
	// Engine
	virtual void setVars(GVars* v) = 0;
	virtual void corePreInit() = 0;
	virtual void coreInit() = 0;
	virtual void corePostInit() = 0;
	virtual void preInit() = 0;
	virtual void init() = 0;
	virtual void postInit() = 0;
};

QT_BEGIN_NAMESPACE

Q_DECLARE_INTERFACE(GModLoaderInterface, "org.ilzcorp.GModLoaderInterface")

QT_END_NAMESPACE

#endif

