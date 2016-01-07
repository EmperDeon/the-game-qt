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

void MRHelper::drawBorder(IVec3 p) {
#   define V(a,b,c) glVertex3d( p.x a 0.5f, p.y b 0.5f, p.z c 0.5f );
	glColor3f(0.0f, 0.0f, 0.0f);
	glLineWidth(3.0f);
	/* PWO: I dared to convert the code to use macros... */
	glBegin( GL_LINES );
	 V(+,-,+); V(+,-,-); V(+,+,-); V(+,+,+);
	 V(+,+,+); V(+,+,-); V(-,+,-); V(-,+,+);
	 V(+,+,+); V(-,+,+); V(-,-,+); V(+,-,+);
	 V(-,-,+); V(-,+,+); V(-,+,-); V(-,-,-);
	 V(-,-,+); V(-,-,-); V(+,-,-); V(+,-,+);
	 V(-,-,-); V(-,+,-); V(+,+,-); V(+,-,-);
	glEnd();

}

void MRHelper::drawCubeS(IVec3 p, byte s, IVec3 c) {
	if(isTopSide(s)    ) drawRectTp(p, c);
	if(isBottomSide(s) ) drawRectBt(p, c);
	if(isLeftSide(s)   ) drawRectLf(p, c);
	if(isRightSide(s)  ) drawRectRg(p, c);
	if(isFrontSide(s)  ) drawRectFr(p, c);
	if(isBackSide(s)   ) drawRectBc(p, c);
}
