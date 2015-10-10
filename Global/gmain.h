#ifndef G_MAIN
#define G_MAIN

#include <QApplication>
#include <Global/gdefines.h>
#include <Global/gutils.h>
#include <Global/gwidgets.h>
#include <Global/gmods.h>

class GLogger;
class GSettings;
class GDeveloper;
class GVars;
class GMods;
class GMWidget;

class GMain : public IMain{
	Q_INTERFACES(IMain)
 QString className = "E-Main";
	GDeveloper* wdev;
	GMWidget* wgt;
	GMods* mods;
public:
	GMain();
	void init();
	void show();
	void destroy();
};

//QT_FORWARD_DECLARE_CLASS(QOpenGLShaderProgram)
//QT_FORWARD_DECLARE_CLASS(QOpenGLTexture)

//class GMWidget : public QOpenGLWidget, protected QOpenGLFunctions
//{
//				Q_OBJECT

//public:
//				explicit GMWidget(QWidget *parent = 0): QOpenGLWidget(parent),
//			clearColor(Qt::black),
//			xRot(0),
//			yRot(0),
//			zRot(0),
//			program(0)
//{
//	memset(textures, 0, sizeof(textures));
//}
//				~GMWidget(){
//		makeCurrent();
//		vbo.destroy();
//		for (int i = 0; i < 6; ++i)
//						delete textures[i];
//		delete program;
//		doneCurrent();
//}

//				QSize minimumSizeHint() const Q_DECL_OVERRIDE;
//				QSize sizeHint() const Q_DECL_OVERRIDE;
//				void rotateBy(int xAngle, int yAngle, int zAngle);
//				void setClearColor(const QColor &color);

//signals:
//				void clicked();

//protected:
//				void initializeGL() Q_DECL_OVERRIDE;
//				void paintGL() Q_DECL_OVERRIDE;
//				void resizeGL(int width, int height) Q_DECL_OVERRIDE;
//				void mousePressEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
//				void mouseMoveEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
//				void mouseReleaseEvent(QMouseEvent *event) Q_DECL_OVERRIDE;

//private:
//				void makeObject();

//				QColor clearColor;
//				QPoint lastPos;
//				int xRot;
//				int yRot;
//				int zRot;
//				QOpenGLTexture *textures[6];
//				QOpenGLShaderProgram *program;
//				QOpenGLBuffer vbo;
//};


#endif
