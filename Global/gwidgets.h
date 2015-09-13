#ifndef G_WIDGETS
#define G_WIDGETS

#include <QtCore>
#include <QtWidgets>
#include <gutils.h>

class Widgets{
public:
	Widgets();
};

class GMWidget : public QOpenGLWidget {// QOpenGLWidget
	Q_OBJECT

public:
	GMWidget();

public slots:
	void animate();

protected:
	virtual void paintEvent(QPaintEvent *event);
};

class GDeveloper : public QWidget{
	Q_OBJECT
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
