#ifndef GLOBALQT_MMODLOADER_H
#define GLOBALQT_MMODLOADER_H
#include <idefines.h>
#include <core/mcoremods.h>
#include <mods/mmods.h>

class MCoreMods;
class MMods;

class MModLoader : public QObject, public IModLoader{
	Q_OBJECT
	Q_PLUGIN_METADATA(IID "org.ilzcorp.IModLoader")
	Q_INTERFACES(IModLoader)

public:

 virtual QString getName()      override;

	virtual void setVars(IVars* v) override;

	virtual void corePreInit()     override;
	virtual void coreInit()        override;
	virtual void corePostInit()    override;

	virtual void preInit()         override;
	virtual void init()            override;
	virtual void postInit()        override;

};

#endif // GLOBALQT_MMODLOADER_H
