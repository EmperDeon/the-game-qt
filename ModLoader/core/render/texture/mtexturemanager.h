#ifndef GLOBALQT_MTEXTUREMANAGER_H
#define GLOBALQT_MTEXTUREMANAGER_H
#include <ModLoader/mdefines.h>

class MMods;

class MTextureManager : public ITextureManager{
	QMap<Imiks, QOpenGLTexture*>* tex;
 MMods* loader;

public:
	MTextureManager(MMods* l);

	virtual void loadTextures(QMap<Imiks, QString> map) override;
	virtual void loadTexture(Imiks, QString name) override;
	virtual QOpenGLTexture *getTexture(Imiks) override;
	virtual void bindTexture(Imiks) override;
};

#endif //GLOBALQT_MTEXTUREMANAGER_H
