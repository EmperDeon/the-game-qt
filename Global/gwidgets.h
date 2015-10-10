#ifndef G_WIDGETS
#define G_WIDGETS

#include <QtCore>
#include <QtWidgets>
#include <Global/gdefines.h>
#include <Global/gutils.h>
#include <Global/gmain.h>

class IRender;

class GMWidget : public QOpenGLWidget {// QOpenGLWidget
	Q_OBJECT
	QString className = "E-MWidget";
 IRender* render;
public:
	GMWidget();

protected:


public slots:
	void animate();

protected:
	virtual void paintEvent(QPaintEvent *event);
	virtual void closeEvent(QCloseEvent *qCloseEvent);
};

class GDeveloper : public QWidget{
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
	GDeveloper();

public slots:
	void showSett();
	void showLevl();
	void showMods();
	void showModl();
	void showPack();
	void showResm();
};

#endif
