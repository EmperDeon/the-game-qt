#include "main.h"

QStringList CM_OEVENTS::getOwList() {
	return {"mLevel"};
}

QStringList CM_OEVENTS::getDpList() {
	return {};
}

void CM_OEVENTS::setVars(IVars *v) {
	IV_VARS = v;
	IV_LOGGER = reinterpret_cast<ILogger*>(v->get("eLogger"));
}

void CM_OEVENTS::preInit() {}

void CM_OEVENTS::init() {}

void CM_OEVENTS::postInit() {}


void *CM_OEVENTS::get(QString name) {
	logI("Get " + name);

	if(name == "mEvents"){
		if(e == nullptr)	e = new MEvents;
		return e;
	}else{
		return nullptr;
	}
}

void *CM_OEVENTS::getO(QString name) {	return nullptr;}

QStringList CM_OEVENTS::getVarsList() {
	return {"mEvents"};
}

ILogger* IV_LOGGER;
IVars*   IV_VARS;