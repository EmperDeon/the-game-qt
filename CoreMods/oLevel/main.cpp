#include "main.h"

QStringList CM_O_LEVEL::getOwList() {
	return {"mLevel"};
}

QStringList CM_O_LEVEL::getDpList() {
	return {};
}

void CM_O_LEVEL::setVars(IVars *v) {
	IV_VARS = v;
	IV_LOGGER = reinterpret_cast<ILogger*>(v->get("eLogger"));
}

void CM_O_LEVEL::preInit() {}

void CM_O_LEVEL::init() {}

void CM_O_LEVEL::postInit() {}


void *CM_O_LEVEL::get(QString name) {
	if(name == "mLevel"){
		if(l == nullptr)	l = new MLevelManager;
		return l;
	}else{
		return nullptr;
	}
}

void *CM_O_LEVEL::getO(QString name) {	Q_UNUSED(name) return nullptr;}

QStringList CM_O_LEVEL::getVarsList() {
	return {"mLevel"};
}

void *CM_O_LEVEL::getN(QString name) {
	return nullptr;
}

void *CM_O_LEVEL::getN(QString name, QJsonObject arg) {
	return nullptr;
}

ILogger* IV_LOGGER;
IVars*   IV_VARS;

