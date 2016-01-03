#ifndef GLOBALQT_IRENDER_H
#define GLOBALQT_IRENDER_H
class IEntity;

class IRObject{ // IRenderObject
public:
	//Render
	virtual int getGlList() = 0;
};

class ICamera{
public:
	virtual void apply() = 0;
 virtual void attachTo(IEntity*) = 0;
};

class IGuiRender{ // 2D
public:
	virtual void render() = 0;

};


class IWorldRender{// 3D
public:
	virtual void init() = 0;
	virtual void render() = 0;

};

#endif //GLOBALQT_IRENDER_H
