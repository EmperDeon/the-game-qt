#ifndef GLOBALQT_MPLAYER_H
#define GLOBALQT_MPLAYER_H
#include <idefines.h>

class MPlayer : public IPlayer{
	float x, y, z;
	float aY, aP; // Yaw and Pitch in radians
	qint32 cX = 0, cZ = 0;

	const QStringList events = {"Keyboard.keyPressMove"};
	QJsonObject keys;

public:
	MPlayer(): x(0.0f), y(0.0f), z(0.0f){}
	MPlayer(float X, float Y, float Z): x(X), y(Y), z(Z){}
	MPlayer(IVec3 v): x(v.x), y(v.y), z(v.z){}

	virtual void moveF() override {move(   0.0f);}
	virtual void moveB() override {move( 3.141f);}
	virtual void moveL() override {move( -1.57f);}
	virtual void moveR() override {move(  1.57f);}

	void move(float r, float d = 0.05f);

	virtual void  moveU(float d = 0.1f) override {y += d;}
	virtual void  moveD(float d = 0.1f) override {y -= d;}

	virtual void  yaw(float y)   override;
	virtual void  pitch(float p) override;

	virtual float yaw()          override {return aY;}
	virtual float pitch()        override {return aP;}

	virtual IVec3 pos()          override {return IVec3(x, y, z);}

	virtual qint32 getCX()       override {return cX;}
	virtual qint32 getCZ()       override {return cZ;}

	void updatePos();
	friend class ICamera;

	// Events
	inline bool isKey(int k, QString v);
	inline int  getFK(QString v);
	virtual void        trigger(QString name, QJsonObject o) override;
	virtual bool        hasEvent(QString name)               override {return events.contains(name); }
	virtual QStringList getEventsList()                      override {return events; }
};

#endif //GLOBALQT_MPLAYER_H
