#ifndef GLOBALQT_MACTIONS_H
#define GLOBALQT_MACTIONS_H
#include <ModLoader/mdefines.h>
#include <ModLoader/core/mcoremods.h>


class MEvents : public IEvents {
 QMultiMap<QString, IEventsReciever*>* map;

public:
	MEvents();

	virtual void triggerEvent (QString group, QString name, QJsonObject o)             override;
	virtual void addNewEventReciever(QString group, IEventsReciever *reciever) override;

	virtual void triggerItemEvent (QString name, QJsonObject o) override;
	virtual void triggerToolEvent (QString name, QJsonObject o) override;
	virtual void triggerBlockEvent(QString name, QJsonObject o) override;
};

#endif //GLOBALQT_MACTIONS_H
