#ifndef GLOBALQT_MAIN_H
#define GLOBALQT_MAIN_H
#include <idefines.h>
#include <mevents.h>

class CM_OEVENTS : public QObject, public ICoreMod{
 Q_OBJECT
	Q_PLUGIN_METADATA(IID "org.ilzcorp.ICoreMod")
	Q_INTERFACES(ICoreMod)

	MEvents* e;

public:

	virtual QStringList getOwList()       override;
	virtual QStringList getDpList()       override;
	virtual QString     getName()         override{ return "oEvents";}

	virtual void        setVars(IVars* v) override;

	virtual void        preInit()         override;
	virtual void        init()            override;
	virtual void        postInit()        override;


	virtual void *get(QString name);
	virtual void *getO(QString name);
	virtual QStringList getVarsList();
};

#endif //GLOBALQT_MAIN_H
