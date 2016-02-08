#include <ModLoader/core/events/mevents.h>

MEvents::MEvents(){map = new QMultiMap<QString, IEventsReciever*>;}

void MEvents::triggerEvent(QString name, QJsonObject o) {
	for(IEventsReciever* e : map->values(name))
		if(e->hasEvent(name))
			e->trigger(name, o);
}

void MEvents::triggerEvent(QString group, QString name, QJsonObject o) {
 triggerEvent(cat(group, name), o);
}

void MEvents::addNewEventReciever(IEventsReciever *reciever) {
	for(QString s : reciever->getEventsList())
  map->insert(s, reciever);
}

void MEvents::triggerItemEvent(QString name, QJsonObject o) {

}

void MEvents::triggerToolEvent(QString name, QJsonObject o) {

}

void MEvents::triggerBlockEvent(QString name, QJsonObject o) {

}
// MEvents
