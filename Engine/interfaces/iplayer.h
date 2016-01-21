#ifndef GLOBALQT_IPLAYER_H
#define GLOBALQT_IPLAYER_H

class ICamera;
class IVec3;


class IEntity{
public:
	virtual IVec3 pos()   = 0;
	virtual float yaw()   = 0;
	virtual float pitch() = 0;

	virtual qint32 getCX() = 0;
	virtual qint32 getCZ() = 0;

	friend class ICamera;
};


class IPlayer : public IEntity{
public:
	virtual void moveF()        = 0;
	virtual void moveB()        = 0;
	virtual void moveL()        = 0;
	virtual void moveR()        = 0;
 virtual void moveU()        = 0;
	virtual void moveD()        = 0;

	virtual void yaw(float y)   = 0;
	virtual void pitch(float p) = 0;
};

#endif //GLOBALQT_IPLAYER_H
