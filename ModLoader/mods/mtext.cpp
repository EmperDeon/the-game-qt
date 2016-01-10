#include <ModLoader/mods/mtext.h>

MTextContainer::MTextContainer(MMods *l) : loader(l), log(l->log), vars(l->vars){

}

void MTextContainer::preInit() {
	QList<QJsonObject> lst;
		foreach(QFileInfo i, QDir("mods/mods").entryInfoList(QDir::Dirs | QDir::NoDotAndDotDot)){
			QDir d("mods/mods/"+i.fileName());
			QJsonObject o = loadJson(d.filePath("text.dat"));
			o.insert("path", d.absolutePath()+"/");
			lst << o;
		}

	//MItemsContainer
	{
		QMap<QString, Imiks> *iidsMap = new QMap<QString, Imiks>;
		QMap<Imiks, IItem *> *itemsMap = new QMap<Imiks, IItem *>;
		QMap<Imiks, QString> texMap;
		QJsonObject t;
		Imiks e;
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
						e = Imiks(cm, ci, ck, cs);

						iidsMap->insert(n, e);
						itemsMap->insert(e, new MItem(t));
						texMap.insert(e, o.value("path").toString() + t["tex"].toString());
					}
			}
		mIids = new MIIds(loader, iidsMap);
		mIic = new MItemsContainer(loader, itemsMap);
  mItex = new MTextureManager(loader);
		mItex->loadTextures(texMap);

		mVarS(mIids, "mIIds");
		mVarS(mIic,  "mItems");
		mVarS(mItex, "mITex");
		mLogD("Items count: "+QString::number(itemsMap->size()));
	}
	//!MItemsContainer
	//MBlocksContainer
	{
		QMap<QString, Imiks> *bidsMap = new QMap<QString, Imiks>;
		QMap<Imiks, IBlock *> *blocksMap = new QMap<Imiks, IBlock *>;
		QMap<Imiks, QString> texMap;
		QJsonObject t;
		Imiks e;
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
						e = Imiks(cm, ci, ck, cs);

						bidsMap->insert(n, e);
						blocksMap->insert(e, new MBlock(t));
						texMap.insert(e, o.value("path").toString() + t["tex"].toString());
					}
			}
		mBids = new MBIds(loader, bidsMap);
		mBic = new MBlocksContainer(loader, blocksMap);
		mBtex = new MTextureManager(loader);
		mBtex->loadTextures(texMap);

		mVarS(mBids, "mBIds");
		mVarS(mBic,  "mBlocks");
		mVarS(mBtex, "mBTex");
		mLogD("Blocks count: "+QString::number(blocksMap->size()));
	}
	//!MBlocksContainer
 //MToolsContainer
	{
		QMap<QString, Imiks> *tidsMap = new QMap<QString, Imiks>;
		QMap<Imiks, ITool *> *toolsMap = new QMap<Imiks, ITool *>;
		QMap<Imiks, QString> texMap;
		QJsonObject t;
		Imiks e;
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
						e = Imiks(cm, ci, ck, cs);

						tidsMap->insert(n, e);
						toolsMap->insert(e, new MTool(t));
						texMap.insert(e, o.value("path").toString() + t["tex"].toString());
					}
			}
		mTids = new MTIds(loader, tidsMap);
		mTic = new MToolsContainer(loader, toolsMap);
		mTtex = new MTextureManager(loader);
		mTtex->loadTextures(texMap);

		mVarS(mTids, "mTIds");
		mVarS(mTic,  "mTools");
		mVarS(mTtex, "mTTex");
		mLogD("Tools count: "+QString::number(toolsMap->size()));
	}
	//!MToolsContainer
}
void MTextContainer::init() {

}
void MTextContainer::postInit() {

}
