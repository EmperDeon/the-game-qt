#ifndef GLOBALQT_MCAMERA_H
#define GLOBALQT_MCAMERA_H
#include <idefines.h>
#include <mrender.h>
#include <GL/glu.h>

class MCamera : public ICamera{
	IEntity* en;

public:

	MCamera();

	virtual void apply()              override;
 virtual void attachTo(IEntity *e) override;
};

inline void gluLookAt(IVec3 p, IVec3 l) {gluLookAt(p.x, p.y, p.z, l.x, l.y, l.z, 0.0f, 1.0f, 0.0f);}

#endif //GLOBALQT_MCAMERA_H
