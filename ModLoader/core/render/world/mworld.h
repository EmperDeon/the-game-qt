#ifndef GLOBALQT_MWORLD_H
#define GLOBALQT_MWORLD_H
#include <ModLoader/mdefines.h>
#include <ModLoader/core/mcoremods.h>
#include <ModLoader/core/render/mhelper.h>

class MWorldRender : public IWorldRender, public MRHelper{// 3D
	QString className = "M-WorldRender";
	MCoreMods* loader;

	float pi=3.141593, k=pi/180;

	GLfloat VertexArray[12][3];
	GLfloat ColorArray[12][4];
	GLubyte IndexArray[20][3];

	void drawAxis();
	void getVertexArray(); // ���������� ������ ������
	void getColorArray();  // ���������� ������ ������ ������
	void getIndexArray();  // ���������� ������ �������� ������


public:
	MWorldRender(MCoreMods* m);
	virtual void init();
	virtual void render();
};


#endif //GLOBALQT_MWORLD_H
