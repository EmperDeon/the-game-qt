#include <ModLoader/core/events/mevents.h>

MEvents::MEvents(){map = new QMultiMap<QString, IEventsReciever*>;}

void MEvents::triggerEvent(QString group, QString name, QJsonObject o) {
 for(IEventsReciever* e : map->values(group))
	 if(e->hasEvent(name))
		 e->trigger(name, o);
}

void MEvents::addNewEventReciever(QString group, IEventsReciever *reciever) {
 map->insert(group, reciever);
}

void MEvents::triggerItemEvent(QString name, QJsonObject o) {

}

void MEvents::triggerToolEvent(QString name, QJsonObject o) {

}

void MEvents::triggerBlockEvent(QString name, QJsonObject o) {

}
// MEvents
