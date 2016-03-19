#ifndef GLOBALQT_IRENDER_H
#define GLOBALQT_IRENDER_H

class IEntity;
class Imiks;
class IChunk;

// RenderObjects
class IRObject{
public:
	//Render
	virtual void   setGlList(GLuint i) = 0;
	virtual GLuint getGlList()         = 0;
	virtual void   onReAlloc()         = 0;
};
// RenderObjects


// Managers
class ITextureManager{
public:
	virtual void             loadTextures(QMap<Imiks, QString> map) = 0;
	virtual void             loadTexture(Imiks, QString name)       = 0;
	virtual void             loadTextures()                         = 0;

	virtual QOpenGLTexture*  getTexture(Imiks)                      = 0;
	virtual void             bindTexture(Imiks)                     = 0;
};
// Managers


// Gui
class IGlWidget : public QOpenGLWidget{
public:
	virtual qint64 getFps() = 0;
};

class IGuiRender{ // 2D
public:
	virtual void render() = 0;
	virtual void close()  = 0;
};
// Gui


// World
class ICamera{
public:
	virtual void apply()            = 0;
	virtual void attachTo(IEntity*) = 0;
};

class IWorldRender{
public:
	virtual void  init()               = 0;
	virtual void  render()             = 0;
	virtual void  close()              = 0;

	virtual void  setPlayer(IEntity* e) = 0;
	// Level-relative
	virtual void  setChunks(QMap<IAChunkPos, IChunk*>* ch) = 0;
	virtual void  reAllocate(int i)     = 0;
	virtual GLuint getFreeList()        = 0;

	virtual void lockPos() = 0;
};
// World

#endif //GLOBALQT_IRENDER_H
