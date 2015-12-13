#ifndef GLOBALQT_MCAMERA_H
#define GLOBALQT_MCAMERA_H
#include <ModLoader/mdefines.h>
#include <ModLoader/core/render/mrender.h>

class MCamera : public ICamera{
	float xP, yP, zP; // Pos
	float xS, yS, zS; // Scale
	float yaw, pitch; // Angles

public:
	MCamera(IBlockPos pos);
	virtual void apply();

	//Pos
	void move(float x, float y, float z) {
		this->xP += x;
		this->yP += y;
		this->zP += z;
	}
	void setPos(float x, float y, float z) {
		this->xP = x;
		this->yP = y;
		this->zP = z;
	}
//Scale
	void scale(float x, float y, float z) {
		this->xS += x;
		this->yS += y;
		this->zS += z;
	}
	//Angle
	void rotate(float y, float p) {	this->yaw += y;	this->pitch += p;}
	void setAngl(float y, float p){	this->yaw  = y;	this->pitch  = p;	}

	virtual Vector3 getPos(){	return Vector3(xP, yP, zP);	}
	virtual float getYaw(){	return yaw;	}
	virtual float getPitch(){	return pitch;	}
	virtual Vector3 getScl(){	return Vector3(xS, yS, zS);	}
};

#endif //GLOBALQT_MCAMERA_H
