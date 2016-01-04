#include "ModLoader/core/render/world/mworld.h"

MWorldRender::MWorldRender(MCoreMods *m): loader(m) {
 this->manager = mVarG(ILevelManager*, "mLevel");
}

void MWorldRender::init() {
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_COLOR_ARRAY);

	MLevelInfo* i= new MLevelInfo;
	i->setName("TestLevel1");

	this->manager->createLevel(i);
	this->level = manager->getCurrentLevel();
	this->loader->queue->waitForDone();
}

void MWorldRender::render() {
	drawAxis();

	// Box of Epileptic
//	this->drawRCube(IVec3(0, 0, 0), 0.15f);
//	this->drawRCube(IVec3(0, 0, 0), 1.0f);
}


void MWorldRender::drawAxis(){
	glLineWidth(3.0f); // ������������ ������ ����� ���������� � ��������
	// �� ������ ������� ������ ����� 1 ������� �� ���������

	glColor4f(1.00f, 0.00f, 0.00f, 1.0f); // ��������������� ���� ����������� ����������
	// ��� x �������� �����
	glBegin(GL_LINES); // ���������� �����
	glVertex3f( 1.0f,  0.0f,  0.0f); // ������ �����
	glVertex3f(-1.0f,  0.0f,  0.0f); // ������ �����
	glEnd();

	glColor4i(0, 128, 0, 255);
	glBegin(GL_LINES);
	// ��� y �������� �����
	glVertex3f( 0.0f,  1.0f,  0.0f);
	glVertex3f( 0.0f, -1.0f,  0.0f);

	glColor4f(0.00f, 0.00f, 1.00f, 1.0f);
	// ��� z ������ �����
	glVertex3f( 0.0f,  0.0f,  1.0f);
	glVertex3f( 0.0f,  0.0f, -1.0f);
	glEnd();
}

void MWorldRender::close() {
 this->level->save();
}
