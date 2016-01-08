#ifndef GLOBALQT_IRENDER_H
#define GLOBALQT_IRENDER_H
class IEntity;

class IRObject{ // IRenderObject
public:
	//Render
	virtual void setGlList(GLuint i) = 0;
	virtual void onReAlloc() = 0;
};

class ICamera{
public:
	virtual void apply() = 0;
 virtual void attachTo(IEntity*) = 0;
};

class IGuiRender{ // 2D
public:
	virtual void render() = 0;
	virtual void close() = 0;
};


class IWorldRender{// 3D
public:
	virtual void init() = 0;
	virtual void render() = 0;
	virtual void close() = 0;

	virtual void setPlayer(IEntity* e) = 0;
	// Level-relative
	virtual void reAllocate(int i) = 0;
	virtual GLuint getFreeList() = 0;
};

#endif //GLOBALQT_IRENDER_H
