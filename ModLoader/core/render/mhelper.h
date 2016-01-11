#ifndef GLOBALQT_MHELPER_H
#define GLOBALQT_MHELPER_H
#include <ModLoader/mdefines.h>
#include <GL/gl.h>

class MRHelper{
 public:

// Rectangles with color
 static void drawRect(IVec3 p, int side, IVec3 c, float r = 0.5f);

	static void drawRectTp(IVec3 p, IVec3 c, float r = 0.5f); // Top
	static void drawRectBt(IVec3 p, IVec3 c, float r = 0.5f); // Bottom
	static void drawRectFr(IVec3 p, IVec3 c, float r = 0.5f); // Front
	static void drawRectBc(IVec3 p, IVec3 c, float r = 0.5f); // Back
	static void drawRectLf(IVec3 p, IVec3 c, float r = 0.5f); // Left
	static void drawRectRg(IVec3 p, IVec3 c, float r = 0.5f); // Right

// Rectangles with texture
 static void drawTRect(IVec3 p, int sid );
 static void drawTRect(IVec3 p, int side, float r = 0.5f);

 static void drawTRectTp(IVec3 p, float r = 0.5f);
	static void drawTRectBt(IVec3 p, float r = 0.5f);
	static void drawTRectFr(IVec3 p, float r = 0.5f);
	static void drawTRectBc(IVec3 p, float r = 0.5f);
	static void drawTRectLf(IVec3 p, float r = 0.5f);
	static void drawTRectRg(IVec3 p, float r = 0.5f);

	static void drawRCube(IVec3 p, float r = 0.5f);
	static void drawCube(IVec3 p, IVec3 c);
	static void drawCube(IVec3 p, IVec3 c, float r = 0.5f);

// Chunk
	static void drawBorder(float x, float y, float z);
	static void drawBorder(IVec3 v){drawBorder(v.x, v.y, v.z);}
	static void drawBorder(IVec3i v){drawBorder(v.x, v.y, v.z);}
	static void drawCubeS(IVec3 vec3, byte s, IVec3 c);
	static void drawTCubeS(IVec3 vec3, byte s);
};

#endif //GLOBALQT_MHELPER_H
