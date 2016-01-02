#ifndef GLOBALQT_IPLAYER_H
#define GLOBALQT_IPLAYER_H

class ICamera;

class IPlayer{
public:
	virtual void moveF() = 0;
	virtual void moveB() = 0;
	virtual void moveL() = 0;
	virtual void moveR() = 0;

	friend class ICamera;
};

#endif //GLOBALQT_IPLAYER_H
