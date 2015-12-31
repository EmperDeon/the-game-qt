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

	QTimer* fps_stabilizer;
public:
	MGlWidget(MCoreMods* m);

protected:
	void initializeGL();
	void resizeGL(int nWidth, int nHeight);
	void paintGL();

	void mousePressEvent(QMouseEvent* pe);
	void mouseMoveEvent(QMouseEvent* pe);
	void mouseReleaseEvent(QMouseEvent* pe);
	void wheelEvent(QWheelEvent* pe);
	void keyPressEvent(QKeyEvent* pe);

	virtual void keyReleaseEvent(QKeyEvent *keyEvent);
};



#endif
