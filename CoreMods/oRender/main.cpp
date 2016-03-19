#include "main.h"

QStringList CM_O_RENDER::getOwList() {	return {"mRender", "nTextureManager"};}

QStringList CM_O_RENDER::getDpList() {	return {};}

void CM_O_RENDER::setVars(IVars *v) {
	IV_VARS = v;
	IV_LOGGER = reinterpret_cast<ILogger*>(v->get("eLogger"));
	IV_SETT = reinterpret_cast<ISettings*>(v->get("eSettings"));
}

void CM_O_RENDER::preInit() {}

void CM_O_RENDER::init() {}

void CM_O_RENDER::postInit() {}


void *CM_O_RENDER::get(QString name) {
	logFF("Get " + name);

	if(name == "mRender"){
		if(r == nullptr){
			r = new MGlWidget;

		}
		return r;
	}else{
		return nullptr;
	}
}

void *CM_O_RENDER::getO(QString name) { Q_UNUSED(name)	return nullptr;}

QStringList CM_O_RENDER::getVarsList() {
	return {"mRender", "nTextureManager"};
}

void *CM_O_RENDER::getN(QString name) {
	if(name == "nTextureManager"){
		return new MTextureManager;
	}else{
		return nullptr;
	}
}

void *CM_O_RENDER::getN(QString name, QJsonObject arg) {
	if(name == "nTextureManager"){
		Q_UNUSED(arg)
		return new MTextureManager;
	}else{
		return nullptr;
	}
}

ILogger* IV_LOGGER;
IVars*   IV_VARS;
ISettings* IV_SETT;

