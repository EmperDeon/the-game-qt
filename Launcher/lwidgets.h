#ifndef WIDGETS_H
#define WIDGETS_H
#define ME_SAVE QString(".zip")

#include <QtWidgets>
#include <QWebView>
#include <QtNetwork>
#include <QtWebKitWidgets>
#include <QtCore>
#include <QtGui>
#include <Launcher/lutils.h>
#include <Launcher/lmain.h>
#include <Global/gmodinterfaces.h>


class LMainWindow;
class GDevelop;
class GSettWidget;
class GLevlWidget;
class GModelWidget;
class GResmWidget;
class LListModel;
class LTableModel;
enum class GLogLevel;
class GLogE;
class GSettingsModel;
class LModsWidget;
class LModEditor;
class LPacker;

class LJsonAWidget : public QWidget{
	Q_OBJECT
	QVBoxLayout* lay;
	QPushButton* b_open;
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
	QVBoxLayout* lay;
	QPushButton* b_open;
	QTableView* list;
	LTableModel* model;
	QJsonObject* obj;
public slots:
	void open();
public:
	LJsonOWidget();
};

class LLogWidget : public QWidget{
	Q_OBJECT
	GLogLevel curr;
	QString last;
	QList<GLogE>* list;

	QTextEdit* w_edit;
	QVBoxLayout* vlay;
	QHBoxLayout* hlay;
	QLabel* w_l;
	QLabel* w_l1;
	QLabel* w_c;
	QPushButton* be;
	QPushButton* bw;
	QPushButton* bi;
	QPushButton* bd;
	QPushButton* bf;
	QPushButton* br;

public slots:
	void switchE();
	void switchW();
	void switchI();
	void switchD();
	void switchF();

	void refresh();
public:
	LLogWidget();
	~LLogWidget();
	void addL(GLogLevel lv, QString cl, QString m);
	void addL(GLogE e);
	void switchL(GLogLevel lv);
};
class GSettWidget : public QWidget{
	Q_OBJECT

	QTabWidget* tabs;
	QMap<QString, QTableView*> wgts;
	QMap<QString, GSettingsModel*> mdls;
	QMap<QString, QJsonObject> map;
	QPushButton* b_save;
	QPushButton* b_load;
	QHBoxLayout* hbox;
	QVBoxLayout* vbox;

public slots:
	void saveS();
	void loadS();
public:
	void clear();
	void init();
	GSettWidget();

};

class LTableManager : public QWidget{
	Q_OBJECT

	LTableModel* model;
	QTableView* table;
	QVBoxLayout* vlay;
	QHBoxLayout* hlay;
	QLineEdit* e_k;
	QLineEdit* e_v;
	QPushButton* b_add;

	QPushButton* b_del;
	QPushButton* b_ok;

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
	QVBoxLayout* vlay;
	QHBoxLayout* hlay;
	QLineEdit* e_k;
	QPushButton* b_add;
	QPushButton* b_del;
	QPushButton* b_ok;

public slots:
	void add();
	void del();
public:
	LListManager(QJsonArray& o, QString t);

};

class GDevelop : public QWidget{
	Q_OBJECT
	LMainWindow* launcher;
	GModLoaderInterface* modloader;
	QVBoxLayout* lay;

	QPushButton* bsett;
	QPushButton* blevl;
	QPushButton* bmods;
	QPushButton* bmodl;
	QPushButton* bpack;
	QPushButton* bmodel;
	QPushButton* bresm;
	QPushButton* bjsono;
	QPushButton* bjsona;

	QPushButton* bparse;
	QPushButton* binit;

	LModEditor * w_mode;
	LPacker * w_pac;
	GSettWidget* wsett;
	GLevlWidget* wlevl;
	GModelWidget* wmodel;
	GResmWidget* wresm;
	LJsonOWidget* jsono;
	LJsonAWidget* jsona;

private slots:
	void parse();
public:
	LModsWidget * w_mod;
	GDevelop(LMainWindow *w);
};

class GLevlWidget : public QWidget{// Level Editor
public:
	GLevlWidget();
};
class GModelWidget : public QWidget{// Level Editor
public:
	GModelWidget();
};
class GResmWidget : public QWidget{// Resource manager
public:
	GResmWidget();
};


class LModsWidget : public QWidget{
Q_OBJECT
	LMainWindow* loader;
	LLogWidget* log;
	LListModel* model;
	QString curr;

	QVBoxLayout* layout;
	QHBoxLayout* l_model;
	QHBoxLayout* l_wgt;
	QPushButton* b_rl;
	QPushButton* b_add;
	QPushButton* b_del;
	QListView* list;
public slots:
	void reload();
	void add();
	void del();
public:
	LModsWidget(LMainWindow* l);
protected:
	void closeEvent(QCloseEvent *event);
};

class LModEditor : public QWidget{// Mods Editor
Q_OBJECT

	QFormLayout* lay;
	QLineEdit* e_file;
	QLineEdit* e_name;
	QLineEdit* e_devl;
	QLineEdit* e_site;
	QTextEdit* e_desc;
	QLineEdit* e_ver;
	QLineEdit* e_dep;
	QLineEdit* e_scr;
	QLineEdit* e_plg;
	QPushButton* b_create;
	QPushButton* b_clear;
	QPushButton* b_dep;
	QPushButton* b_other;
	QComboBox* c_type;
	LTableManager* w_oth;
	LListManager* w_dep;

	QString type;
	QJsonArray* depend;
	QJsonObject* other;
	LLogWidget* log;
	LMainWindow* loader;
public slots:
	void bcreate();
	void bclear();
	void bdep();
	void bother();
	void ctype(int i);
public:
	QString REVISION;
	LModEditor(LMainWindow* l);
};

class LPacker : public QWidget{
Q_OBJECT
	LMainWindow* loader;
	LLogWidget* log;
public:
	LPacker(LMainWindow* l);
};

#endif // WIDGETS_H
