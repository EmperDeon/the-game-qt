#include <texture/mtexturemanager.h>

MTextureManager::MTextureManager(){
 this->tex = new QMap<Imiks, QOpenGLTexture*>;
	this->toAdd = new QMap<Imiks, QString>;
}

void MTextureManager::loadTextures(QMap<Imiks, QString> map){
 for(Imiks k : map.keys()){
	 loadTexture(k, map.value(k));
 }
}

void MTextureManager::loadTexture(Imiks k, QString v) {
// QOpenGLTexture* t = new QOpenGLTexture(QImage(v));
	this->toAdd->insert(k, v);
}

void MTextureManager::loadTextures() {
 for(Imiks k : toAdd->keys()){
	 QOpenGLTexture *t = new QOpenGLTexture(QImage(toAdd->value(k)));
	 this->tex->insert(k, t);
 }
}

QOpenGLTexture *MTextureManager::getTexture(Imiks k) {	return this->tex->value(k); }
void MTextureManager::bindTexture(Imiks k) {this->tex->value(k)->bind(); }

