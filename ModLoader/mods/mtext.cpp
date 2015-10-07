#include <ModLoader/mods/mtext.h>
#include <ModLoader/mods/mcontainers.h>

MTextContainer::MTextContainer(MMods *l) : loader(l), log(l->log), vars(l->vars){

}

void MTextContainer::preInit() {
	QList<QJsonObject> lst;
		foreach(QFileInfo i, QDir("mods/mods").entryInfoList(QDir::Dirs | QDir::NoDotAndDotDot)){
			lst << loadJson(QDir("mods/mods/"+i.fileName()).filePath("text.dat"));
		}

	// Mids
	QMap<QString, Emiks*>* itemsMap = new QMap<QString, Emiks*>;
	QJsonObject t;
	QString lm = "", li = "", lk = "", ls = "";
	int cm = 0, ci = 0, ck = 0, cs = 0;

		foreach(QJsonObject o, lst) {
				foreach(QJsonValue v, o["items"].toArray()) {
					t = v.toObject();
					if(o["name"].toString() != lm) {cm++; lm = o["name"].toString(); }
					if(t["ii"].toString() != li){ ci++; li = t["ii"].toString(); }
					if(t["ik"].toString() != lk){ ck++; lk = t["ik"].toString(); }
					if(t["is"].toString() != ls){ cs++; ls = t["is"].toString(); }

					itemsMap->insert(lm + "^" + li + "^" + lk + "^" + ls, new Emiks(cm, ci, ck, cs));
				}
		}
	MIds* mids = new MIds(loader, itemsMap);
	this->vars->set(mids, "mIds");
	//!Mids


}
void MTextContainer::init() {

}
void MTextContainer::postInit() {

}
