#ifndef GLOBALQT_LWIDGETS_H
#define GLOBALQT_LWIDGETS_H
#include <ldefines.h>
#include <lutils.h>
#include <lmain.h>
#include <lwmodels.h>
#include <widgets/llevel.h>
#include <widgets/lmodeditor.h>
#include <widgets/lmodel.h>
#include <widgets/lmods.h>
#include <widgets/lresources.h>

class LModEditor;
class LMainWindow;
class LTableModel;
class LListModel;
class LModsWidget;
class LSettingsModel;

// Json Viewers
class LJsonAWidget : public QWidget{
	Q_OBJECT

	QListView* list;
	LListModel* model;
	QJsonArray* obj;
public slots:
	void open();
public:
	LJsonAWidget();
};

class LJsonOWidget : public QWidget{
	Q_OBJECT

	QTableView* list;
	LTableModel* model;
	QJsonObject* obj;
public slots:
	void open();
public:
	LJsonOWidget();
};

class LTableManager : public QWidget{
	Q_OBJECT

	LTableModel* model;
	QTableView* table;
	QLineEdit* e_k;
	QLineEdit* e_v;

public slots:
	void add();
	void del();

public:
	LTableManager(QJsonObject& o, QString t);
};

class LListManager : public QWidget{
	Q_OBJECT

	LListModel* model;
	QListView* list;
	QLineEdit* e_k;

public slots:
	void add();
	void del();
public:
	LListManager(QJsonArray& o, QString t);

};
// Json Viewers


// LSettings
class LSettWidget : public QWidget{
 Q_OBJECT

	QTabWidget* tabs;
	QMap<QString, QTableView*>* wgts;
	QMap<QString, LSettingsModel *>* mdls;
	QMap<QString, QJsonObject>* map;

public slots:
	void saveS();
	void loadS();

public:
	LSettWidget();
	void clear();
	void init();
};
// LSettings


// LPacker
class LPacker : public QWidget{
Q_OBJECT

public:
	LPacker();
};
// LPacker


// LDevelop
class LDevelop : public QWidget{
Q_OBJECT
	LMainWindow* launcher;

	LModEditor * w_mode;
	LPacker * w_pac;
	LSettWidget * wsett;
	LLevlWidget * wlevl;
	LModelWidget * wmodel;
	LResmWidget * wresm;
	LJsonOWidget* jsono;
	LJsonAWidget* jsona;

public:
	LDevelop(LMainWindow *w);
	LModsWidget* w_mod;

private slots:
	void parse();
};
// LDevelop

#endif //GLOBALQT_LWIDGETS_H
