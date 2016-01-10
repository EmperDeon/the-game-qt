#include "ModLoader/core/render/world/mworld.h"

MWorldRender::MWorldRender(MCoreMods *m): loader(m) {
 this->manager = mVarG(ILevelManager*, "mLevel");
	this->listMutex = new QMutex;
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

	if(currentActive > 0){
		listMutex->lock();

		for ( int i = 0 ; i < currentActive ; i++) {
			glCallList(currentIndex + i);
		}

		listMutex->unlock();
	}

 selectBlock();
	// Box of Epileptic
//	this->drawRCube(IVec3(0, 0, 0), 0.15f);
//	this->drawRCube(IVec3(0, 0, 0), 1.0f);
}

void MWorldRender::selectBlock() {
 IVec3i c(en->pos()),t;
	float sc = 0.001f;
 float x = 0.0f;

	IVec3 i(
		cosf(en->pitch()) * cosf(en->yaw()),
		sinf(en->yaw()),
		sinf(en->pitch()) * cosf(en->yaw())
	);

 while(x < 5.0f){
		x += sc;
	 t.x = c.x + int(i.x * x);
		t.y = c.y + int(i.y * x);
	 t.z = c.z + int(i.z * x);

		if(c != t){
			c = t;
			if(level->isBlock(c)) break;
		}
 }
	if(c != IVec3i(en->pos())) drawBorder(c);
}


void MWorldRender::drawAxis(){
	glLineWidth(3.0f);

	glColor4f(1.00f, 0.00f, 0.00f, 1.0f);
	glBegin(GL_LINES);
	glVertex3f( 1.0f,  0.0f,  0.0f);
	glVertex3f(-1.0f,  0.0f,  0.0f);
	glEnd();

	glColor4i(0, 128, 0, 255);
	glBegin(GL_LINES);
	// ��� y �������� �����
	glVertex3f( 0.0f,  1.0f,  0.0f);
	glVertex3f( 0.0f, -1.0f,  0.0f);

	glColor4f(0.00f, 0.00f, 1.00f, 1.0f);
	glVertex3f( 0.0f,  0.0f,  1.0f);
	glVertex3f( 0.0f,  0.0f, -1.0f);
	glEnd();
}

void MWorldRender::close() {
 this->level->save();
}
void MWorldRender::reAllocateC(ILevel* l){ l->reAllocate(this);}
void MWorldRender::reAllocate(int i) {
	if(currentGened){
		glDeleteLists(currentIndex, currentGenCount);
	}
 this->currentIndex = glGenLists(i + 5);
	this->currentGenCount = i + 5;
	this->currentActive = 0;
 mLogI(QString("reAllocate: %1").arg(i));

 reAllocateC(this->level);
}

GLuint MWorldRender::getFreeList() {
	QMutexLocker l(this->listMutex);
	if(currentActive >= currentGenCount){
		reAllocate(currentGenCount);
	}
	return currentIndex + currentActive++;
}
