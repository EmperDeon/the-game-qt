#ifndef G_MODS
#define G_MODS

#include <QtCore>
#include <Global/gmodinterfaces.h>

class mods : public QObject
{
    Q_OBJECT
public:
    explicit mods(QObject *parent = 0);

signals:

public slots:
};

class GMods : public QObject {
	Q_OBJECT
	GModLoaderInterface* modloader;

public:
	GMods();
	void coreInit();
	void init();

};

#endif
