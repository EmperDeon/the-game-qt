#ifndef GLOBALQT_MAIN_H
#define GLOBALQT_MAIN_H
#include <cm_defines.h>

extern ILogger* CM_LOG;

class CMEvents : public IEvents {
	IEvents* org;

public:
	CMEvents(IVars *v, IEvents *o);

	virtual void triggerEvent (QString name, QJsonObject o)                override;
	virtual void triggerEvent (QString group, QString name, QJsonObject o) override;
	virtual void addNewEventReciever(IEventsReciever *reciever) override;

	virtual void triggerItemEvent (QString name, QJsonObject o) override;
	virtual void triggerToolEvent (QString name, QJsonObject o) override;
	virtual void triggerBlockEvent(QString name, QJsonObject o) override;
};


class TestCore1Main : public QObject, public ICoreMod{
 Q_OBJECT
	Q_PLUGIN_METADATA(IID "org.ilzcorp.ICoreMod")
	Q_INTERFACES(ICoreMod)

	IVars* vars;
	ILogger* logger;
 CMEvents* events;
public:

	virtual QStringList getOwList()       override;
	virtual QStringList getDpList()       override;
	virtual QString     getName()         override{ return "TestCore1";}

	virtual void        setVars(IVars* v) override;

	virtual void        preInit()         override;
	virtual void        init()            override;
	virtual void        postInit()        override;


	virtual void *get(QString name);
	virtual void *getO(QString name);
	virtual QStringList getVarsList();
};

#endif //GLOBALQT_MAIN_H
