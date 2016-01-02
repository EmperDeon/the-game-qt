#ifndef GLOBALQT_MHELPER_H
#define GLOBALQT_MHELPER_H
#include <ModLoader/mdefines.h>

#include <GL/gl.h>

class MRHelper : public IRHelper{
 public:
  static void drawRect(IVec3 p1, IVec3 p2, bool side, IVec3 c);
 	static void drawRect(IVec3 p1, IVec3 p2, int sideD, bool side, IVec3 c);
};

#endif //GLOBALQT_MHELPER_H
