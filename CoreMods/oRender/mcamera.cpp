#include <mcamera.h>

MCamera::MCamera() {}

void MCamera::apply() {
 if(en) {
	 float cY = cosf(en->yaw());
		IVec3 p = en->pos(), l = IVec3();
	 
	 l.x = p.x + cosf(en->pitch()) * cY;
	 l.y = p.y + sinf(en->yaw());
	 l.z = p.z + sinf(en->pitch()) * cY;

	 gluLookAt(p, l);
 }
}

void MCamera::attachTo(IEntity *e) {
 this->en = e;
}
