#ifndef GLOBALQT_MAIN_H
#define GLOBALQT_MAIN_H
#include <idefines.h>
#include <mlevel.h>

class CM_O_LEVEL : public QObject, public ICoreMod{
 Q_OBJECT
	Q_PLUGIN_METADATA(IID "org.ilzcorp.ICoreMod")
	Q_INTERFACES(ICoreMod)

	MLevelManager* l = nullptr;

public:

	virtual QStringList getOwList()       override;
	virtual QStringList getDpList()       override;
	virtual QString     getName()         override{ return "oLevel";}

	virtual void        setVars(IVars* v) override;

	virtual void        preInit()         override;
	virtual void        init()            override;
	virtual void        postInit()        override;


	virtual void *get(QString name);
	virtual void *getO(QString name);

	virtual void *getN(QString name);
	virtual void *getN(QString name, QJsonObject arg);

	virtual QStringList getVarsList();
};

#endif //GLOBALQT_MAIN_H
