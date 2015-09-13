#ifndef G_MAIN
#define G_MAIN

#include <QApplication>
#include <gutils.h>
#include <grender.h>
#include <gwidgets.h>

class GLogger;
class GSettings;
class GDeveloper;
class GVars;
class GVar;

extern GLogger GV_LOGGER;
extern GRenderer GV_RENDER;
extern GSettings GV_SETTINGS;
extern GVars GV_VARS;

#define SETTINGS_FILE "settings.dat"
#define CLASS_NAME "Not_Defined"

#define logE(ms) GV_LOGGER.log(GLogLevel::ERR,   CLASS_NAME, ms)
#define logW(ms) GV_LOGGER.log(GLogLevel::WARN,  CLASS_NAME, ms)
#define logI(ms) GV_LOGGER.log(GLogLevel::INFO,  CLASS_NAME, ms)
#define logD(ms) GV_LOGGER.log(GLogLevel::DEBUG, CLASS_NAME, ms)
#define logF(ms) GV_LOGGER.log(GLogLevel::FINE,  CLASS_NAME, ms)

#define varG(cl, s) qobject_cast<cl>(GV_VARS.get(s))
#define varS(cl, s) GV_VARS.set(cl, s)


void init();
void destroy();
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