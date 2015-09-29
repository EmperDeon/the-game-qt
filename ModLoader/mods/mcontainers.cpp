#include <ModLoader/mods/mcontainers.h>

MIds::MIds() {

}
Emiks* MIds::get(QString m, QString i, QString k, int s) {
	if(mods.contains(m))
  return mods[m];
	else{
		MModIds* t = new MModIds(m, last++);
		mods[m] = t;
		return t->get(i, k, s);
	}
}

MModIds::MModIds(QString m, int i) {
 this->name = m;
	this->num = i;
}
Emiks* MModIds::get(QString i, QString k, int s) {
	QString ti = i + "^";
	if(map.contains(i))
		return map[i];
	else{
		MModIds* t = new MModIds(i, last++);
		map[i] = t;
		return t->get(i, k, s);
	}
}

