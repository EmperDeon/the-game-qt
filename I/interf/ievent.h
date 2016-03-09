#ifndef GLOBALQT_IEVENT_H
#define GLOBALQT_IEVENT_H

class QString;
class QJsonObject;
class QStringList;

class IEventsReciever;

// Actions
class IEvents {
public:
	virtual void triggerEvent (QString name, QJsonObject o)                    = 0;
	virtual void triggerEvent (QString group, QString name, QJsonObject o)     = 0;
 virtual void addNewEventReciever(IEventsReciever *reciever) = 0;

	virtual void triggerItemEvent (QString name, QJsonObject o) = 0;
	virtual void triggerToolEvent (QString name, QJsonObject o) = 0;
	virtual void triggerBlockEvent(QString name, QJsonObject o) = 0;
};

class IEventsReciever{
public:
	virtual void        trigger       (QString name, QJsonObject o) = 0;
	virtual bool        hasEvent      (QString name)                = 0;
	virtual QStringList getEventsList ()                            = 0;
};
//Actions

#endif //GLOBALQT_IEVENT_H
