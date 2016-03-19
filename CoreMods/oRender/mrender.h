#ifndef GLOBALQT_MRENDER_H
#define GLOBALQT_MRENDER_H
#include <QtOpenGL/QtOpenGL>
#include <idefines.h>
#include <mcamera.h>
#include <gui/mgui.h>
#include <world/mworld.h>

class MCamera;
class MPlayer;
class MRInput;
class MRKeyboardInput;
class MRMouseInput;
class MRKeyboardInit;

class MGlWidget : public IGlWidget{
	Q_OBJECT

 MCamera* cam;
	IPlayer* player;
	IWorldRender* world;
	IGuiRender* gui;

	// Fps
 qint64 fps = 0;
	QElapsedTimer* fps_t;
	QTimer* fps_stabilizer;

	MRInput* input;
	IEvents* events;
	bool paused = false;

public:
	MGlWidget();
 virtual	qint64 getFps() override {return fps;}
 virtual void loadingFinished();

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

	inline bool isMovement(int k){return keysMov.contains(k);}
	inline bool isOneTime (int k){return keysOnT.contains(k);}
 void insertKeysTo(QList<int> &list, QStringList key);

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
