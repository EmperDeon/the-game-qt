#ifndef G_WIDGETS
#define G_WIDGETS

#include <QtCore>
#include <QtWidgets>
#include "Engine/edefines.h"
#include "Engine/eutils.h"
#include "Engine/emain.h"

class EDeveloper : public QWidget{
	Q_OBJECT
	QString className = "E-Developer";
	QVBoxLayout* lay;
	QPushButton* bsett;
	QPushButton* blevl;
	QPushButton* bmods;
	QPushButton* bmodl;
	QPushButton* bpack;
	QPushButton* bresm;

public:
	EDeveloper();

public slots:
	void showSett();
	void showLevl();
	void showMods();
	void showModl();
	void showPack();
	void showResm();
};

#endif
