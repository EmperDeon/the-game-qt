#include <grender.h>
GRender::GRender():QObject(){

}

GRenderer::GRenderer():QObject(){

}

GRenderer::~GRenderer(){

}

void GRenderer::init()
{

}

void GRenderer::render(QPaintDevice* dev){
    QPainter painter;
    painter.begin(dev);
    painter.setRenderHint(QPainter::Antialiasing);

    glClearColor(0.0, 0.0, 0.0, 0.0);
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0, 1.0, 1.0);
    glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0);
    glBegin(GL_POLYGON);
    glVertex2f(-0.5, -0.5);
    glVertex2f(-0.5, 0.5);
    glVertex2f(0.5, 0.5);
    glVertex2f(0.5, -0.5);
    glEnd();
    glFlush();

    painter.end();
}

GRenderer GV_RENDER;
