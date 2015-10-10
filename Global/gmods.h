#ifndef G_MODS
#define G_MODS

#include <QtCore>
#include <Global/gdefines.h>

class GModLoaderInterface;

//class mods : public QObject
//{
//    Q_OBJECT
//public:
//    explicit mods(QObject *parent = 0);
//
//signals:
//
//public slots:
//};

class GMods : public QObject {
	Q_OBJECT
	QString className = "E-Mods";
	GModLoaderInterface* modloader;
	QMap<QString, QString>* modloaderlist;
private:
	void initModLoaders();
public:
	GMods();
	void coreInit();
	void init();

};

#endif
