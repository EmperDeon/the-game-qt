#ifndef GLOBALQT_MCAMERA_H
#define GLOBALQT_MCAMERA_H
#include <ModLoader/mdefines.h>
#include <ModLoader/core/render/mrender.h>

class MCamera : public ICamera{
	float xP, yP, zP; // Pos
	float yaw, pitch; // Angles

	float xSense = 0.004f, ySense = 0.004f;

	bool wFocus = true;
	int wWidth, wHeight;
public:
	const QCursor* pointer;

	MCamera(IBlockPos pos);
	virtual void apply();
 virtual void resize(int w, int h);
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
 //Focus
	bool getFocus(){return wFocus;}
	void setFocus(bool n){this->wFocus = n;}
	void switchFocus(){this->wFocus = !this->wFocus;}

	virtual IVec3 getPos(){	return IVec3(xP, yP, zP);	}
	virtual float getYaw(){	return yaw;	}
	virtual float getPitch(){	return pitch;	}
	virtual IVec3 getScl(){	return IVec3(xS, yS, zS);	}
};

#endif //GLOBALQT_MCAMERA_H
