#ifndef GLOBALQT_MCONTAINERS_H
#define GLOBALQT_MCONTAINERS_H

#include <QtCore>
#include <Global/gmodinterfaces.h>
#include <ModLoader/mmodloader.h>

class MModsParser{
	ModLoader* loader;

public:
	MModsParser(ModLoader* m);

};

class MIds : public IModsIds {
 Q_INTERFACES(IItemIds)
 ModLoader* loader;
	QMap<QString, Emiks*>* mods;
 Emiks* mnull;

public:
 MIds(ModLoader *m, QMap<QString, Emiks*>* l);
	Emiks* get(QString m, QString i, QString k, int s) Q_DECL_OVERRIDE;
};



#endif //GLOBALQT_MCONTAINERS_H
