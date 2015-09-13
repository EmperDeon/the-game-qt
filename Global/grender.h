#ifndef G_RENDER
#define G_RENDER

#include <QtWidgets>
#include <QtOpenGL/QtOpenGL>

class GRender : public QObject{
    Q_OBJECT

public:
				GRender();
};

class GRenderer : public QObject{
    Q_OBJECT

public:
				GRenderer();
    void init();
    void render(QPaintDevice* dev);

				~GRenderer();
};

#endif
