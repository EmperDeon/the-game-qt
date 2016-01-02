#ifndef GLOBALQT_MCAMERA_H
#define GLOBALQT_MCAMERA_H
#include <ModLoader/mdefines.h>
#include <ModLoader/core/render/mrender.h>
#include <GL/glu.h>

class MCamera : public ICamera{
	IEntity* en;
public:

	MCamera();
	virtual void apply();
 virtual void attachTo(IEntity *e);
};


inline void gluLookAt(IVec3 p, IVec3 l){
	gluLookAt(p.x, p.y, p.z,
	          l.x, l.y, l.z,
	          0.0f, 1.0f, 0.0f);
}

#endif //GLOBALQT_MCAMERA_H
