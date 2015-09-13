#ifndef MODSWIDGET_H
#define MODSWIDGET_H

#include <QtCore>
#include <QtWidgets>
#include <QtGui>
#include <../Launcher/lwidgets.h>
#include <mmodloader.h>
#include <mparser.h>
#include <mutils.h>

class ModLoader;
class MListModel;
class MTableModel;
class MListManager;
class MTableManager;

class MModsWidget : public QWidget{
	Q_OBJECT
	ModLoader* loader;
	LLogWidget* log;
	MListModel* model;
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
	MModsWidget(ModLoader* l);
protected:
	void closeEvent(QCloseEvent *event);
};

class MModEditor : public QWidget{// Mods Editor
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
	MTableManager* w_oth;
	MListManager* w_dep;

	QString type;
	QJsonArray* depend;
	QJsonObject* other;
	LLogWidget* log;
	ModLoader* loader;
public slots:
	void bcreate();
	void bclear();
	void bdep();
	void bother();
	void ctype(int i);
public:
	QString REVISION;
	MModEditor(ModLoader* l);
};

class MPacker : public QWidget{
	Q_OBJECT
ModLoader* loader;
	LLogWidget* log;
public:
	MPacker(ModLoader* l);
};

#endif // MODSWIDGET_H
