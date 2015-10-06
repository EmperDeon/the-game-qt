#include <ModLoader/core/mrender.h>

MRender::MRender(MCoreMods* m){
 this->loader = m;
}

MRender::~MRender(){

}

void MRender::init(){

}

void MRender::render(QPaintDevice* dev){
	QPainter painter;
	painter.begin(dev);
	painter.setRenderHint(QPainter::Antialiasing);

	glClearColor(0.0, 0.0, 0.0, 0.0);
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1.0, 1.0, 1.0);
	glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0);
	glBegin(GL_POLYGON);
	glVertex2f((GLfloat) -0.5, (GLfloat) -0.5);
	glVertex2f((GLfloat) -0.5, 0.5);
	glVertex2f(0.5, 0.5);
	glVertex2f(0.5, (GLfloat) -0.5);
	glEnd();
	glFlush();

	painter.end();
}