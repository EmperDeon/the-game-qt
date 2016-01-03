#include "ModLoader/core/render/mhelper.h"

float r(){return (qrand() % 101)*0.01f;}
IVec3 rc(){return IVec3(r(), r(), r());}

void MRHelper::drawRect(int side, IVec3 p, IVec3 c) {
 switch (side){
	  case 0:drawRectTp(p, c);break;
		 case 1:drawRectBt(p, c);break;
		 case 2:drawRectFr(p, c);break;
		 case 3:drawRectBc(p, c);break;
		 case 4:drawRectLf(p, c);break;
		 case 5:drawRectRg(p, c);break;
		 default:;
 }
}
void MRHelper::drawRect(int side, IVec3 p, float r, IVec3 c) {
	switch (side){
		case 0:drawRectTp(p, r, c);break;
		case 1:drawRectBt(p, r, c);break;
		case 2:drawRectFr(p, r, c);break;
		case 3:drawRectBc(p, r, c);break;
		case 4:drawRectLf(p, r, c);break;
		case 5:drawRectRg(p, r, c);break;
		default:;
	}
}

void MRHelper::drawRectTp(IVec3 p, float r, IVec3 c) {
 glBegin(GL_QUADS);
	glColor3f(c.x, c.y, c.z);
	glVertex3f(p.x + r, p.y + r, p.z - r);
	glVertex3f(p.x - r, p.y + r, p.z - r);
	glVertex3f(p.x - r, p.y + r, p.z + r);
	glVertex3f(p.x + r, p.y + r, p.z + r);
	glEnd();
}

void MRHelper::drawRectBt(IVec3 p, float r, IVec3 c) {
	glBegin(GL_QUADS);
	glColor3f(c.x, c.y, c.z);
	glVertex3f(p.x + r, p.y - r, p.z + r);
	glVertex3f(p.x - r, p.y - r, p.z + r);
	glVertex3f(p.x - r, p.y - r, p.z - r);
	glVertex3f(p.x + r, p.y - r, p.z - r);
	glEnd();
}

void MRHelper::drawRectFr(IVec3 p, float r, IVec3 c) {
	glBegin(GL_QUADS);
	glColor3f(c.x, c.y, c.z);
	glVertex3f(p.x + r, p.y + r, p.z + r);
	glVertex3f(p.x - r, p.y + r, p.z + r);
	glVertex3f(p.x - r, p.y - r, p.z + r);
	glVertex3f(p.x + r, p.y - r, p.z + r);
	glEnd();
}

void MRHelper::drawRectBc(IVec3 p, float r, IVec3 c) {
	glBegin(GL_QUADS);
	glColor3f(c.x, c.y, c.z);
	glVertex3f(p.x + r, p.y - r, p.z - r);
	glVertex3f(p.x - r, p.y - r, p.z - r);
	glVertex3f(p.x - r, p.y + r, p.z - r);
	glVertex3f(p.x + r, p.y + r, p.z - r);
	glEnd();
}

void MRHelper::drawRectLf(IVec3 p, float r, IVec3 c) {
	glBegin(GL_QUADS);
	glColor3f(c.x, c.y, c.z);
	glVertex3f(p.x - r, p.y + r, p.z + r);
	glVertex3f(p.x - r, p.y + r, p.z - r);
	glVertex3f(p.x - r, p.y - r, p.z - r);
	glVertex3f(p.x - r, p.y - r, p.z + r);
	glEnd();
}

void MRHelper::drawRectRg(IVec3 p, float r, IVec3 c) {
	glBegin(GL_QUADS);
	glColor3f(c.x, c.y, c.z);
	glVertex3f(p.x + r, p.y + r, p.z - r);
	glVertex3f(p.x + r, p.y + r, p.z + r);
	glVertex3f(p.x + r, p.y - r, p.z + r);
	glVertex3f(p.x + r, p.y - r, p.z - r);
	glEnd();
}

void MRHelper::drawCube(IVec3 p, IVec3 c) {
 drawRectTp(p, c);
	drawRectBt(p, c);
	drawRectFr(p, c);
	drawRectBc(p, c);
	drawRectLf(p, c);
	drawRectRg(p, c);
}

void MRHelper::drawCube(IVec3 p, float r, IVec3 c) {
	drawRectTp(p, r, c);
	drawRectBt(p, r, c);
	drawRectFr(p, r, c);
	drawRectBc(p, r, c);
	drawRectLf(p, r, c);
	drawRectRg(p, r, c);
}

void MRHelper::drawRCube(IVec3 p, float r) {
	drawRectTp(p, r, rc());
	drawRectBt(p, r, rc());
	drawRectFr(p, r, rc());
	drawRectBc(p, r, rc());
	drawRectLf(p, r, rc());
	drawRectRg(p, r, rc());
}

