#ifndef M_RENDER
#define M_RENDER

#include <QtWidgets>
#include <QtOpenGL/QtOpenGL>
#include <ModLoader/mdefines.h>
#include <ModLoader/core/mcoremods.h>
#include <ModLoader/core/render/mcamera.h>
#include <ModLoader/core/render/gui/mgui.h>
#include <ModLoader/core/render/world/mworld.h>

class MCoreMods;
class MCamera;

class MGlWidget : public QGLWidget{
	QString className = "M-Render";
	MCoreMods* loader;

 MCamera* cam;
	IWorldRender* world;
	IGuiRender* gui;

	// Fps
 qint64 fps = 0;
	QElapsedTimer* fps_t;
	QTimer* fps_stabilizer;
 // !Fps
public:
	MGlWidget(MCoreMods* m);
	qint64 getFps(){return fps;}
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

	virtual void keyReleaseEvent(QKeyEvent *keyEvent);
};



#endif
