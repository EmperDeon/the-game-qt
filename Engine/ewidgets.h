#ifndef G_WIDGETS
#define G_WIDGETS

#include <QtCore>
#include <QtWidgets>
#include "Engine/edefines.h"
#include "Engine/eutils.h"
#include "Engine/emain.h"

class IRender;

class EMWidget : public QOpenGLWidget {// QOpenGLWidget
	Q_OBJECT
	QString className = "E-MWidget";
 IRender* render;
public:
	EMWidget();

protected:


public slots:
	void animate();

protected:
	virtual void paintEvent(QPaintEvent *event);
	virtual void closeEvent(QCloseEvent *qCloseEvent);
};

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
