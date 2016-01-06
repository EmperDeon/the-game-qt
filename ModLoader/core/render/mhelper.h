#ifndef GLOBALQT_MHELPER_H
#define GLOBALQT_MHELPER_H
#include <ModLoader/mdefines.h>

#include <GL/gl.h>

class MRHelper{
 public:

 	static void drawRect(int side, IVec3 p, IVec3 c);
 	static void drawRect(int side, IVec3 p, float r, IVec3 c);

	 static void drawRectTp(IVec3 p, float r, IVec3 c); // Top
	 static void drawRectBt(IVec3 p, float r, IVec3 c); // Bottom
	 static void drawRectFr(IVec3 p, float r, IVec3 c); // Front
	 static void drawRectBc(IVec3 p, float r, IVec3 c); // Back
	 static void drawRectLf(IVec3 p, float r, IVec3 c); // Left
	 static void drawRectRg(IVec3 p, float r, IVec3 c); // Right

	 static void drawRectTp(IVec3 p, IVec3 c){ drawRectTp(p, 0.5f, c); }
	 static void drawRectBt(IVec3 p, IVec3 c){ drawRectBt(p, 0.5f, c); }
	 static void drawRectFr(IVec3 p, IVec3 c){ drawRectFr(p, 0.5f, c); }
	 static void drawRectBc(IVec3 p, IVec3 c){ drawRectBc(p, 0.5f, c); }
	 static void drawRectLf(IVec3 p, IVec3 c){ drawRectLf(p, 0.5f, c); }
	 static void drawRectRg(IVec3 p, IVec3 c){ drawRectRg(p, 0.5f, c); }

	 static void drawRCube(IVec3 p, float r);
	 static void drawCube(IVec3 p, IVec3 c);
	 static void drawCube(IVec3 p, float r, IVec3 c);

	// Chunk
	 static void drawBorder(IVec3 vec3);
	 static void drawCubeS(IVec3 vec3, byte s, IVec3 c);
};

#endif //GLOBALQT_MHELPER_H
