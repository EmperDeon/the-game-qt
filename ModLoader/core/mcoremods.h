#ifndef GLOBALQT_MCOREMODS_H
#define GLOBALQT_MCOREMODS_H
#include <idefines.h>
#include <ModLoader/mutils.h>
#include <ModLoader/mods/mmods.h>

class MEvents;
class MLevelManager;
class MVarSelect;
class MVarSelectWidget;

class MCoreMods : public IVarsLoader{
	IMain* main;
 QThread* t_ren;

//	MPerformanceWidget *perf;
	IEvents *events;
	ILevelManager* level;

 QList<ICoreMod*>* modList;
 MVarSelect * vselect;
public:
	QThreadPool* queue;
//	MGlWidget *render;

	MCoreMods();

	void parseOwerwrites();
	void loadPlugins();
	void preInit();

	void init();

	void postInit();


	virtual void *get(QString name)   override;
 virtual void* getO(QString name)  override;
	virtual QStringList getVarsList() override;

	friend class MVarSelect;
	friend class MVarSelectWidget;

	IVarsLoader *findMod(QString n);
};

class MVarSelect {
	QMap<QString, IVarsLoader*>* map;

public:
 MVarSelect(MCoreMods *core);

	void* getVar(QString name);
	void* getOVar(QString name);
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
	int currI() const;
};
#endif //GLOBALQT_MCOREMODS_H
