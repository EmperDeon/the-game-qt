#ifndef GLOBALQT_MAIN_H
#define GLOBALQT_MAIN_H
#include <idefines.h>
#include <mrender.h>
#include <perf/mperfw.h>
#include <texture/mtexturemanager.h>

class CM_O_RENDER : public QObject, public ICoreMod{
 Q_OBJECT
	Q_PLUGIN_METADATA(IID "org.ilzcorp.ICoreMod")
	Q_INTERFACES(ICoreMod)

	IGlWidget* r = nullptr;
	MPerformanceWidget* perf = nullptr;

 QOpenGLContext* context;

public:

	virtual QStringList getOwList()       override;
	virtual QStringList getDpList()       override;
	virtual QString     getName()         override{ return "oRender";}

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
