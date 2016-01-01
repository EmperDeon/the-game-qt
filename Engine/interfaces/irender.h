#ifndef GLOBALQT_IRENDER_H
#define GLOBALQT_IRENDER_H

class ICamera{
public:
	virtual void apply() = 0;
	virtual void resize(int w, int h) = 0;
	//Pos
	virtual void move(float x, float y, float z) = 0;
	virtual void setPos(float x, float y, float z) = 0;
	//Scale
	virtual void scale(float x, float y, float z) = 0;
 //Angle
	virtual void rotate(float y, float p) = 0;
	virtual void setAngl(float y, float p) = 0;

	virtual Vector3 getPos() = 0;
	virtual float getYaw() = 0;
	virtual float getPitch() = 0;
	virtual Vector3 getScl() = 0;
};

class IGuiRender{ // 2D
public:
	virtual void render() = 0;

};

class IRHelper{

};

class IWorldRender{// 3D
public:
	virtual void init() = 0;
	virtual void render() = 0;

};

#endif //GLOBALQT_IRENDER_H
