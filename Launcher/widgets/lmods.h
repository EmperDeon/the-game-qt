#ifndef GLOBALQT_LMODS_H
#define GLOBALQT_LMODS_H
#include <ldefines.h>
#include <lmain.h>

class LMainWindow;
class LListModel;

class LModsWidget : public QWidget{
Q_OBJECT
	LMainWindow* loader;
	LListModel* model;

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

#endif //GLOBALQT_LMODS_H
