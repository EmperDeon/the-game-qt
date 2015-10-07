#include <ModLoader/mods/mcontainers.h>

MIds::MIds(MMods *m, QMap<QString, Emiks*>* l) {
 this->loader = m;
	this->mods = l;
	this->mnull = new Emiks(0,0,0,0);
}
Emiks* MIds::get(QString m, QString i, QString k, int s) {
	QString t = m+"^"+i+"^"+k+"^"+QString::number(s);
	if(mods->contains(t))
  return mods->value(t);
	else{
		loader->log->log(GLogLevel::ERR, "MIds","Map doesn't contains "+t+", unexpected result (returning 0,0,0,0)");
		return mnull;
	}
}

