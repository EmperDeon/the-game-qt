#ifndef GLOBALQT_MACTIONS_H
#define GLOBALQT_MACTIONS_H
#include <idefines.h>

class MEvents : public IEvents {
 QMultiMap<QString, IEventsReciever*>* map;

public:
	MEvents();

	inline QString cat(QString s1, QString s2) {return s1 + "." + s2;}

	virtual void triggerEvent (QString name, QJsonObject o)                    override;
	virtual void triggerEvent (QString group, QString name, QJsonObject o)     override;
	virtual void addNewEventReciever(IEventsReciever *reciever) override;

	virtual void triggerItemEvent (QString name, QJsonObject o) override;
	virtual void triggerToolEvent (QString name, QJsonObject o) override;
	virtual void triggerBlockEvent(QString name, QJsonObject o) override;
};

#endif //GLOBALQT_MACTIONS_H
