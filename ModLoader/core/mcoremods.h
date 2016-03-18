#ifndef GLOBALQT_MCOREMODS_H
#define GLOBALQT_MCOREMODS_H
#include <idefines.h>
#include <mutils.h>
#include <mods/mmods.h>

class MVarSelect;
class MVarSelectWidget;

class MCoreMods{
	IMain* main;
 QList<ICoreMod*>* modList;
 MVarSelect *vSelect;

	inline bool contains(QStringList a, QStringList b);
public:
	MCoreMods();

	void parseOverwrites();
	void loadPlugins();
	void preInit();

	void init();

	void postInit();

	IVarsLoader *findMod(QString n);

	friend class MVarSelect;
	friend class MVarSelectWidget;
};

class MVarSelect : public IVarsSelect {
	QMap<QString, IVarsLoader*>* map;

public:
 MVarSelect(MCoreMods *core);

	virtual void* get(QString name)                   override;
 virtual void* getN(QString name)                  override;
 virtual void* getN(QString name, QJsonObject arg) override;

	virtual void* get(QString mod, QString name)                   override;
	virtual void* getN(QString mod, QString name)                  override;
	virtual void* getN(QString mod, QString name, QJsonObject arg) override;

	void continueLoad();
};

class MVarSelectWidget : public QWidget{
	Q_OBJECT

 QMultiMap<QString, QString>* map; // k - var, v - mod name/modloader
	QMap<QString, QString>* smap;

	QTableWidget* table;
 int px = -1;

public slots:
	void cellClicked(int row, int column);
 void save();

public:
	MVarSelectWidget(MCoreMods *core);

protected:
	virtual void closeEvent(QCloseEvent *qCloseEvent) override;
};
#endif //GLOBALQT_MCOREMODS_H
