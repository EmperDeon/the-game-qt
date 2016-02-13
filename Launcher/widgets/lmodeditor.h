#ifndef GLOBALQT_LMODEDITOR_H
#define GLOBALQT_LMODEDITOR_H
#include <Launcher/ldefines.h>
#include <Launcher/lwmodels.h>
#include <Launcher/lwidgets.h>

class LTextModWidgetModel;
class LTableManager;
class LListManager;
class LModEditor;

class LTextModWidgetEditor : public QWidget{
 Q_OBJECT

	QTableView* table;
	LTextModWidgetModel * model;

	QPushButton* b_add;
	QPushButton* b_del;

	QJsonArray* ob;
	QList<QLineEdit*>* list;
	QStringList nameKeys;
	QStringList nameVals;

private slots:
	void sadd();
	void sdel();

public:
	LTextModWidgetEditor(QStringList keys, QStringList vals, QJsonArray* a);

	friend class LTextModWidgetModel;
};

class LTextModEditor : public QWidget{
 Q_OBJECT

	QJsonObject* obj;
	QJsonArray* jItems;
	QJsonArray* jBlocks;
	QJsonArray* jTools;

	QTabWidget* tabs;
	LTextModWidgetEditor * w_items;
	LTextModWidgetEditor * w_blocks;
	LTextModWidgetEditor * w_tools;

private slots:
	void ssave();
	void sfill();

public:
	LTextModEditor(QJsonObject* o);
};

class LScriptModEditor : public QWidget{
 Q_OBJECT

	QJsonObject* obj;
public:
	LScriptModEditor(QJsonObject* o);
};

class LModEditor : public QWidget{// Mods Editor
 Q_OBJECT

protected:
	QLineEdit* e_file;
	QLineEdit* e_name;
	QLineEdit* e_devl;
	QLineEdit* e_site;
	QTextEdit* e_desc;
	QLineEdit* e_ver;
	QLineEdit* e_dep;
	QLineEdit* e_plg;
	QComboBox* c_type;
	LTableManager* w_oth;
	LListManager* w_dep;

	QString type;
	QJsonArray* depend;
	QJsonObject* other;

	QJsonObject* textMod;
	LTextModEditor* textModE;

	QJsonObject* scriptMod;
	LScriptModEditor* scriptModE;

	QString pluginFile;

private slots:
	void splugin();
	virtual void bcreate();
	void bclear();
	void bdep();
	void bother();
	void ctype(int i);

public:
	QString REVISION;
	LModEditor();
};


class LModFixer : public LModEditor{
Q_OBJECT

public slots:
	virtual void bcreate();
public:
	LModFixer(QString pluginFile);
};

#endif //GLOBALQT_LMODEDITOR_H
