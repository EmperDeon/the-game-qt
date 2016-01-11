#include <ModLoader/core/render/texture/mtexturemanager.h>

MTextureManager::MTextureManager(){
 this->tex = new QMap<Imiks, QOpenGLTexture*>;
}

void MTextureManager::loadTextures(QMap<Imiks, QString> map){
 for(Imiks k : map.keys()){
	 loadTexture(k, map.value(k));
 }
}

void MTextureManager::loadTexture(Imiks k, QString v) {
 QOpenGLTexture* t = new QOpenGLTexture(QImage(v));
	t->setBorderColor(1.0f, 1.0f, 1.0f, 1.0f);
	t->setFormat(QOpenGLTexture::RGB8I);
	this->tex->insert(k, t);
}

QOpenGLTexture *MTextureManager::getTexture(Imiks k) {	return this->tex->value(k); }
void MTextureManager::bindTexture(Imiks k) {this->tex->value(k)->bind(); }

