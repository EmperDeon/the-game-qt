#include <ModLoader/mods/mtext.h>
#include <ModLoader/mods/mcontainers.h>

MTextContainer::MTextContainer(MMods *l) : loader(l), log(l->log), vars(l->vars){

}

void MTextContainer::preInit() {
	QList<QJsonObject> lst;
		foreach(QFileInfo i, QDir("mods/mods").entryInfoList(QDir::Dirs | QDir::NoDotAndDotDot)){
			lst << loadJson(QDir("mods/mods/"+i.fileName()).filePath("text.dat"));
		}

	//MItemsContainer
	{
		QMap<QString, Emiks *> *iidsMap = new QMap<QString, Emiks *>;
		QMap<Emiks *, IItem *> *itemsMap = new QMap<Emiks *, IItem *>;
		QJsonObject t;
		Emiks *e;
		QString lm = "", li = "", lk = "", ls = "", m, i, k, s, n;
		int cm = 0, ci = 0, ck = 0, cs = 0;

			foreach(QJsonObject o, lst) {
				m = o["name"].toString();
					foreach(QJsonValue v, o["items"].toArray()) {
						t = v.toObject();
						i = t["ii"].toString();
						k = t["ik"].toString();
						s = t["is"].toString();

						if (m != lm) { cm++;lm = m; }
						if (i != li) { ci++;li = i; }
						if (k != lk) { ck++;lk = k; }
						if (s != ls) { cs++;ls = s; }

						n = lm + "^" + li + "^" + lk + "^" + ls;
						e = new Emiks(cm, ci, ck, cs);

						iidsMap->insert(n, e);
						itemsMap->insert(e, new MItem(t));
					}
			}
		MIIds *mids = new MIIds(loader, iidsMap);
		MItemsContainer *mic = new MItemsContainer(loader, itemsMap);

		mVarS(mids, "mIIds");
		mVarS(mic, "mItems");
		mLogD("Items count: "+QString::number(itemsMap->size()));
	}
	//!MItemsContainer
	//MBlocksContainer
	{
		QMap<QString, Emiks *> *bidsMap = new QMap<QString, Emiks *>;
		QMap<Emiks *, IBlock *> *blocksMap = new QMap<Emiks *, IBlock *>;
		QJsonObject t;
		Emiks *e;
		QString lm = "", li = "", lk = "", ls = "", m, i, k, s, n;
		int cm = 0, ci = 0, ck = 0, cs = 0;

			foreach(QJsonObject o, lst) {
				m = o["name"].toString();
					foreach(QJsonValue v, o["blocks"].toArray()) {
						t = v.toObject();
						i = t["ii"].toString();
						k = t["ik"].toString();
						s = t["is"].toString();

						if (m != lm) { cm++;lm = m; }
						if (i != li) { ci++;li = i; }
						if (k != lk) { ck++;lk = k; }
						if (s != ls) { cs++;ls = s; }

						n = lm + "^" + li + "^" + lk + "^" + ls;
						e = new Emiks(cm, ci, ck, cs);

						bidsMap->insert(n, e);
						blocksMap->insert(e, new MBlock(t));
					}
			}
		MBIds *mids = new MBIds(loader, bidsMap);
		MBlocksContainer *mic = new MBlocksContainer(loader, blocksMap);

		mVarS(mids, "mBIds");
		mVarS(mic, "mItems");
		mLogD("Blocks count: "+QString::number(blocksMap->size()));
	}
	//!MBlocksContainer
 //MToolsContainer
	{
		QMap<QString, Emiks *> *tidsMap = new QMap<QString, Emiks *>;
		QMap<Emiks *, ITool *> *toolsMap = new QMap<Emiks *, ITool *>;
		QJsonObject t;
		Emiks *e;
		QString lm = "", li = "", lk = "", ls = "", m, i, k, s, n;
		int cm = 0, ci = 0, ck = 0, cs = 0;

			foreach(QJsonObject o, lst) {
				m = o["name"].toString();
					foreach(QJsonValue v, o["tools"].toArray()) {
						t = v.toObject();
						i = t["ii"].toString();
						k = t["ik"].toString();
						s = t["is"].toString();

						if (m != lm) {cm++;	lm = m;	}
						if (i != li) {ci++;	li = i;	}
						if (k != lk) {ck++;	lk = k;	}
						if (s != ls) {cs++;	ls = s;	}

						n = lm + "^" + li + "^" + lk + "^" + ls;
						e = new Emiks(cm, ci, ck, cs);

						tidsMap->insert(n, e);
						toolsMap->insert(e, new MTool(t));
					}
			}
		MTIds *mids = new MTIds(loader, tidsMap);
		MToolsContainer *mic = new MToolsContainer(loader, toolsMap);

		mVarS(mids, "mTIds");
		mVarS(mic, "mTools");
		mLogD("Tools count: "+QString::number(toolsMap->size()));
	}
	//!MToolsContainer
}
void MTextContainer::init() {

}
void MTextContainer::postInit() {

}
