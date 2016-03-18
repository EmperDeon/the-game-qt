#include "main.h"

QStringList CM_O_EVENTS::getOwList() {
	return {"mEvents"};
}

QStringList CM_O_EVENTS::getDpList() {
	return {};
}

void CM_O_EVENTS::setVars(IVars *v) {
	IV_VARS = v;
	IV_LOGGER = reinterpret_cast<ILogger*>(v->get("eLogger"));
}

void CM_O_EVENTS::preInit() {}

void CM_O_EVENTS::init() {}

void CM_O_EVENTS::postInit() {}


void *CM_O_EVENTS::get(QString name) {
	logFF("Get " + name);

	if(name == "mEvents"){
		if(e == nullptr)	e = new MEvents;
		return e;
	}else{
		return nullptr;
	}
}

void *CM_O_EVENTS::getO(QString name) { Q_UNUSED(name)	return nullptr;}

QStringList CM_O_EVENTS::getVarsList() {
	return {"mEvents"};
}

void *CM_O_EVENTS::getN(QString name) {
	if(name == "Events"){
		return new MEvents;
	}else{
		return nullptr;
	}
}

void *CM_O_EVENTS::getN(QString name, QJsonObject arg) {
	return getN(name);
}

ILogger* IV_LOGGER;
IVars*   IV_VARS;