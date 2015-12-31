#ifndef GLOBALQT_MWORLD_H
#define GLOBALQT_MWORLD_H
#include <ModLoader/mdefines.h>
#include <ModLoader/core/mcoremods.h>

class MWorldRender : public IWorldRender{// 3D
	QString className = "M-WorldRender";
	MCoreMods* loader;

	float pi=3.141593, k=pi/180;

	GLfloat VertexArray[12][3];
	GLfloat ColorArray[12][4];
	GLubyte IndexArray[20][3];

	void drawAxis();
	void getVertexArray(); // определить массив вершин
	void getColorArray();  // определить массив цветов вершин
	void getIndexArray();  // определить массив индексов вершин


public:
	MWorldRender(MCoreMods* m);
	virtual void init();
	virtual void render();

	void renderPolygon(float x1, float y1, float z1, float x2, float y2, float z3);
	void renderCube(float x, float y, float z);
};


#endif //GLOBALQT_MWORLD_H
