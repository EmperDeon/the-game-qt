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
};


class MRInput : public QObject{
	Q_OBJECT
 MGlWidget* render;

	QTimer* inp_stabilizer;

protected slots:
 void updateInput();

public:
	MRKeyboardInput* keybr;
	MRMouseInput* mouse;

	MRInput(MGlWidget* w);
};

class MRKeyboardInput : public QObject{
	Q_OBJECT
	MGlWidget* render;

	QList<int>* keyList;

public slots:
	void keyPressEvent(QKeyEvent* pe);
	void keyReleaseEvent(QKeyEvent *ke);

public:
	MRKeyboardInput(MGlWidget* w);
 void update();
};

class MRMouseInput : public QObject{
	Q_OBJECT
	MGlWidget* render;

	QCursor* pointer;
	QCursor* normalp;

	float xSense = 0.0025f, ySense = 0.0025f;
	bool wFocus = true;

public slots:
	void mousePressEvent(QMouseEvent* pe);
	void mouseMoveEvent(QMouseEvent* pe);
	void mouseReleaseEvent(QMouseEvent* pe);
	void wheelEvent(QWheelEvent* pe);

public:
	MRMouseInput(MGlWidget* w);
 void switchFocus();
	void update();
};
#endif
