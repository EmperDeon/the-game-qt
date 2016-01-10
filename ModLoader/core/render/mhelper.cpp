#include "ModLoader/core/render/mhelper.h"

float r(){return (qrand() % 101)*0.01f;}
IVec3 rc(){return IVec3(r(), r(), r());}

#define glCf(c) glColor3f(c.x, c.y, c.z)
#define glVf(a,b,c) glVertex3f(p.x a r, p.y b r, p.z c r);
#define glTf(a,b) glTexCoord2f(a, b);

// Color
void MRHelper::drawRect(IVec3 p, int side, IVec3 c, float r) {
	switch (side){
		case 0:			drawRectTp(p, c, r);break;
		case 1:			drawRectBt(p, c, r);break;
		case 2:			drawRectFr(p, c, r);break;
		case 3:			drawRectBc(p, c, r);break;
		case 4:			drawRectLf(p, c, r);break;
		case 5:			drawRectRg(p, c, r);break;
		default:;
	}
}


void MRHelper::drawRectTp(IVec3 p, IVec3 c, float r) {
 glBegin(GL_QUADS);
	glColor3f(c.x, c.y, c.z);
	glVertex3f(p.x + r, p.y + r, p.z - r);
	glVertex3f(p.x - r, p.y + r, p.z - r);
	glVertex3f(p.x - r, p.y + r, p.z + r);
	glVertex3f(p.x + r, p.y + r, p.z + r);
	glEnd();
}

void MRHelper::drawRectBt(IVec3 p, IVec3 c, float r) {
	glBegin(GL_QUADS);
	glColor3f(c.x, c.y, c.z);
	glVertex3f(p.x + r, p.y - r, p.z + r);
	glVertex3f(p.x - r, p.y - r, p.z + r);
	glVertex3f(p.x - r, p.y - r, p.z - r);
	glVertex3f(p.x + r, p.y - r, p.z - r);
	glEnd();
}

void MRHelper::drawRectFr(IVec3 p, IVec3 c, float r) {
	glBegin(GL_QUADS);
	glColor3f(c.x, c.y, c.z);
	glVertex3f(p.x + r, p.y + r, p.z + r);
	glVertex3f(p.x - r, p.y + r, p.z + r);
	glVertex3f(p.x - r, p.y - r, p.z + r);
	glVertex3f(p.x + r, p.y - r, p.z + r);
	glEnd();
}

void MRHelper::drawRectBc(IVec3 p, IVec3 c, float r) {
	glBegin(GL_QUADS);
	glColor3f(c.x, c.y, c.z);
	glVertex3f(p.x + r, p.y - r, p.z - r);
	glVertex3f(p.x - r, p.y - r, p.z - r);
	glVertex3f(p.x - r, p.y + r, p.z - r);
	glVertex3f(p.x + r, p.y + r, p.z - r);
	glEnd();
}

void MRHelper::drawRectLf(IVec3 p, IVec3 c, float r) {
	glBegin(GL_QUADS);
	glColor3f(c.x, c.y, c.z);
	glVertex3f(p.x - r, p.y + r, p.z + r);
	glVertex3f(p.x - r, p.y + r, p.z - r);
	glVertex3f(p.x - r, p.y - r, p.z - r);
	glVertex3f(p.x - r, p.y - r, p.z + r);
	glEnd();
}

void MRHelper::drawRectRg(IVec3 p, IVec3 c, float r) {
	glBegin(GL_QUADS);
	glColor3f(c.x, c.y, c.z);
	glVertex3f(p.x + r, p.y + r, p.z - r);
	glVertex3f(p.x + r, p.y + r, p.z + r);
	glVertex3f(p.x + r, p.y - r, p.z + r);
	glVertex3f(p.x + r, p.y - r, p.z - r);
	glEnd();
}
// Color

// Texture
void MRHelper::drawTRect(IVec3 p, int side) {
	switch (side){
		case 0:drawTRectTp(p);break;
		case 1:drawTRectBt(p);break;
		case 2:drawTRectFr(p);break;
		case 3:drawTRectBc(p);break;
		case 4:drawTRectLf(p);break;
		case 5:drawTRectRg(p);break;
		default:;
	}
}

void MRHelper::drawTRect(IVec3 p, int side, float r) {
	switch (side){
		case 0:drawTRectTp(p, r);break;
		case 1:drawTRectBt(p, r);break;
		case 2:drawTRectFr(p, r);break;
		case 3:drawTRectBc(p, r);break;
		case 4:drawTRectLf(p, r);break;
		case 5:drawTRectRg(p, r);break;
		default:;
	}
}


void MRHelper::drawTRectTp(IVec3 p, float r) {
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f);glVertex3f(p.x + r, p.y + r, p.z - r);
	glTexCoord2f(1.0f, 0.0f);glVertex3f(p.x - r, p.y + r, p.z - r);
	glTexCoord2f(1.0f, 1.0f);glVertex3f(p.x - r, p.y + r, p.z + r);
	glTexCoord2f(0.0f, 1.0f);glVertex3f(p.x + r, p.y + r, p.z + r);
	glEnd();
}

void MRHelper::drawTRectBt(IVec3 p, float r) {
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f);glVertex3f(p.x + r, p.y - r, p.z + r);
	glTexCoord2f(1.0f, 0.0f);glVertex3f(p.x - r, p.y - r, p.z + r);
	glTexCoord2f(1.0f, 1.0f);glVertex3f(p.x - r, p.y - r, p.z - r);
	glTexCoord2f(0.0f, 1.0f);glVertex3f(p.x + r, p.y - r, p.z - r);
	glEnd();
}

void MRHelper::drawTRectFr(IVec3 p, float r) {
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f);glVertex3f(p.x + r, p.y + r, p.z + r);
	glTexCoord2f(1.0f, 0.0f);glVertex3f(p.x - r, p.y + r, p.z + r);
	glTexCoord2f(1.0f, 1.0f);glVertex3f(p.x - r, p.y - r, p.z + r);
	glTexCoord2f(0.0f, 1.0f);glVertex3f(p.x + r, p.y - r, p.z + r);
	glEnd();
}

void MRHelper::drawTRectBc(IVec3 p, float r) {
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f);glVertex3f(p.x + r, p.y - r, p.z - r);
	glTexCoord2f(1.0f, 0.0f);glVertex3f(p.x - r, p.y - r, p.z - r);
	glTexCoord2f(1.0f, 1.0f);glVertex3f(p.x - r, p.y + r, p.z - r);
	glTexCoord2f(0.0f, 1.0f);glVertex3f(p.x + r, p.y + r, p.z - r);
	glEnd();
}

void MRHelper::drawTRectLf(IVec3 p, float r) {
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f);glVertex3f(p.x - r, p.y + r, p.z + r);
	glTexCoord2f(1.0f, 0.0f);glVertex3f(p.x - r, p.y + r, p.z - r);
	glTexCoord2f(1.0f, 1.0f);glVertex3f(p.x - r, p.y - r, p.z - r);
	glTexCoord2f(0.0f, 1.0f);glVertex3f(p.x - r, p.y - r, p.z + r);
	glEnd();
}

void MRHelper::drawTRectRg(IVec3 p, float r) {
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f);glVertex3f(p.x + r, p.y + r, p.z - r);
	glTexCoord2f(1.0f, 0.0f);glVertex3f(p.x + r, p.y + r, p.z + r);
	glTexCoord2f(1.0f, 1.0f);glVertex3f(p.x + r, p.y - r, p.z + r);
	glTexCoord2f(0.0f, 1.0f);glVertex3f(p.x + r, p.y - r, p.z - r);
	glEnd();
}
// Texture

// Cube
void MRHelper::drawCube(IVec3 p, IVec3 c) {
	drawRectTp(p, c);
	drawRectBt(p, c);
	drawRectFr(p, c);
	drawRectBc(p, c);
	drawRectLf(p, c);
	drawRectRg(p, c);
}

void MRHelper::drawCube(IVec3 p, IVec3 c, float r) {
	drawRectTp(p, c, r);
	drawRectBt(p, c, r);
	drawRectFr(p, c, r);
	drawRectBc(p, c, r);
	drawRectLf(p, c, r);
	drawRectRg(p, c, r);
}

void MRHelper::drawRCube(IVec3 p, float r) {
	drawRectTp(p, rc(), r);
	drawRectBt(p, rc(), r);
	drawRectFr(p, rc(), r);
	drawRectBc(p, rc(), r);
	drawRectLf(p, rc(), r);
	drawRectRg(p, rc(), r);
}

void MRHelper::drawBorder(float x, float y, float z) {
#   define V(a,b,c) glVertex3d( x a 0.505f, y b 0.505f, z c 0.505f );
	glColor3f(0.0f, 0.0f, 0.0f);
	glLineWidth(3.0f);

	glBegin( GL_LINES );
	 V(+,+,-); V(+,-,-);
	 V(+,-,-); V(+,-,+);
	 V(+,-,+); V(+,+,+);
	 V(+,+,+); V(+,+,-);

 	V(-,+,-); V(-,-,-);
 	V(-,-,-); V(-,-,+);
 	V(-,-,+); V(-,+,+);
 	V(-,+,+); V(-,+,-);

	 V(+,-,-); V(-,-,-);
 	V(+,-,+); V(-,-,+);
 	V(+,+,+); V(-,+,+);
	 V(+,+,-); V(-,+,-);
	glEnd();

}

void MRHelper::drawCubeS(IVec3 p, byte s, IVec3 c) {
	if(isTopSide(s)    ) drawRectTp(p, c);
	if(isBottomSide(s) ) drawRectBt(p, c);
	if(isLeftSide(s)   ) drawRectLf(p, c);
	if(isRightSide(s)  ) drawRectRg(p, c);
	if(isFrontSide(s)  ) drawRectFr(p, c);
	if(isBackSide(s)   ) drawRectBc(p, c);

//	drawBorder(p);
}

void MRHelper::drawTCubeS(IVec3 p, byte s) {
	if(isTopSide(s)    ) drawTRectTp(p);
	if(isBottomSide(s) ) drawTRectBt(p);
	if(isLeftSide(s)   ) drawTRectLf(p);
	if(isRightSide(s)  ) drawTRectRg(p);
	if(isFrontSide(s)  ) drawTRectFr(p);
	if(isBackSide(s)   ) drawTRectBc(p);

//	drawBorder(p);
}