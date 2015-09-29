#ifndef GLOBALQT_MCONTAINERS_H
#define GLOBALQT_MCONTAINERS_H

#include <QtCore>
#include <Global/gmodinterfaces.h>

class MModIds {
 QMap<QString, Emiks*> map;
 QString name;
	int last, num;

public:
	MModIds(QString m, int i);
	Emiks* get(QString i, QString k, int s);

};

class MIds : public IModsIds {
 Q_INTERFACES(IItemIds)

	QMap<QString, MModIds*> mods;
	int last;
public:
 MIds();
	Emiks* get(QString m, QString i, QString k, int s) Q_DECL_OVERRIDE;
};



#endif //GLOBALQT_MCONTAINERS_H
