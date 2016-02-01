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
 QTimer* inp_stabilizer;
	// Keyboard
	QList<int>* keyList;

	// MouseControl
 QCursor* pointer;
	float xSense = 0.0025f, ySense = 0.0025f;
	bool wFocus = true;

public:
	MGlWidget();
	qint64 getFps(){return fps;}
private slots:
	void updateInput();

protected:
	void initializeGL();
	void resizeGL(int nWidth, int nHeight);
	void paintGL();

	void mousePressEvent(QMouseEvent* pe);
	void mouseMoveEvent(QMouseEvent* pe);
	void mouseReleaseEvent(QMouseEvent* pe);
	void wheelEvent(QWheelEvent* pe);
	void keyPressEvent(QKeyEvent* pe);

	void switchFocus();

	virtual void keyReleaseEvent(QKeyEvent *ke);
	void closeEvent(QCloseEvent *event);
};



#endif
