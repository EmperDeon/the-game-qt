#ifndef GLOBALQT_MRENDER_H
#define GLOBALQT_MRENDER_H
#include <QtOpenGL/QtOpenGL>
#include <ModLoader/mdefines.h>
#include <ModLoader/core/player/mplayer.h>
#include <ModLoader/core/render/mcamera.h>
#include <ModLoader/core/render/gui/mgui.h>
#include <ModLoader/core/render/world/mworld.h>

class MCamera;
class MPlayer;
class MRInput;
class MRKeyboardInput;
class MRMouseInput;
class MRKeyboardInit;

class MGlWidget : public QGLWidget{
	Q_OBJECT

 MCamera* cam;
	MPlayer* player;
	IWorldRender* world;
	IGuiRender* gui;

	// Fps
 qint64 fps = 0;
	QElapsedTimer* fps_t;
	QTimer* fps_stabilizer;

	MRInput* input;
	bool paused = false;

public:
	MGlWidget();
	qint64 getFps(){return fps;}

protected:
	void initializeGL();
	void resizeGL(int nWidth, int nHeight);
	void paintGL();

	void closeEvent(QCloseEvent *event);

	void keyPressEvent(QKeyEvent* pe);
	void keyReleaseEvent(QKeyEvent *ke);
	void mousePressEvent(QMouseEvent* pe);
	void mouseMoveEvent(QMouseEvent* pe);
	void mouseReleaseEvent(QMouseEvent* pe);
	void wheelEvent(QWheelEvent* pe);
	friend class MRInput;
	friend class MRKeyboardInput;
	friend class MRMouseInput;
	friend class MRKeyboardInit;
};


class MRInput : public QObject{
	Q_OBJECT
 MGlWidget* render;

	QTimer* inp_stabilizer;

protected slots:
 void updateInput();

public slots:
	void keyInitEnd();

public:
	MRKeyboardInput* keybr;
	MRMouseInput* mouse;

	MRInput(MGlWidget* w);
};

class MRKeyboardInput{
	MGlWidget* render;

	QList<int>* keyList;
	QJsonObject& keys;

	QList<int> keysMov;
	QList<int> keysOnT;

	bool isMovement(int k){return keysMov.contains(k);}
	bool isOneTime (int k){return keysOnT.contains(k);}

public:
	MRKeyboardInput(MGlWidget* w);
 void update();

	void keyPressEvent(QKeyEvent* pe);
	void keyReleaseEvent(QKeyEvent *ke);
 inline int k(QString s)const {return keys[s].toInt();}

	friend class MRKeyboardInit;
	friend class MGlWidget;
};

class MRMouseInput{
	MGlWidget* render;

	QCursor* pointer;
	QCursor* normalp;

	float xSense = 0.0025f, ySense = 0.0025f;


public:
	MRMouseInput(MGlWidget* w);
 void switchFocus();
	void update();

	void mousePressEvent(QMouseEvent* pe);
	void mouseMoveEvent(QMouseEvent* pe);
	void mouseReleaseEvent(QMouseEvent* pe);
	void wheelEvent(QWheelEvent* pe);
};

class MRKeyboardInit : public QWidget{
	QLabel* lab;
	MRKeyboardInput* in;

	QStringList k;
	QStringList v;
	int current = -1;

public:
	MRKeyboardInit(MRKeyboardInput* i);
	void keyPressEvent(QKeyEvent* pe);
 void next();
};

#endif
