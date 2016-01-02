#ifndef GLOBALQT_MPLAYER_H
#define GLOBALQT_MPLAYER_H
#include <ModLoader/mdefines.h>

class MPlayer : public IPlayer{
	float x, y, z;
	float aY, aP; // Yaw and Pitch in radians

public:
	MPlayer(float X, float Y, float Z): x(X), y(Y), z(Z){}
	MPlayer(IVec3 v): x(v.x), y(v.y), z(v.z){}

	virtual void moveF();
	virtual void moveB();
	virtual void moveL();
	virtual void moveR();

	void move(float r);

	virtual void moveU(){y += 0.5f;}
	virtual void moveD(){y -= 0.5f;}

	virtual void yaw(float y);
	virtual void pitch(float p);

	virtual float yaw(){return aY;}
	virtual float pitch(){return aP;}

	virtual IVec3 pos(){return IVec3(x, y, z);}

	friend class ICamera;
};

#endif //GLOBALQT_MPLAYER_H
