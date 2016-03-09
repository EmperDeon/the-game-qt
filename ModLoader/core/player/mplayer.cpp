#include <ModLoader/core/player/mplayer.h>


void MPlayer::move(float r, float d) {
	x = x + cosf(aP + r) * d;
	z = z + sinf(aP + r) * d;
	updatePos();
}

void MPlayer::yaw(float y) {
 this->aY += y;
	aY = aY >  1.57f ?  1.57f : aY;
	aY = aY < -1.57f ? -1.57f : aY;
}

void MPlayer::pitch(float p) {
 this->aP += p;
	aP = aP > 6.28f ? 0.0f : aP;
	aP = aP < 0.0f ? 6.28f : aP;
}

void MPlayer::updatePos() {
 qint32 ctX = x / CHUNK_SIZE;
	qint32 ctZ = z / CHUNK_SIZE;

	cX = x < 0 ? ctX - 1 : ctX;
	cZ = z < 0 ? ctZ - 1 : ctZ;
}

void MPlayer::trigger(QString name, QJsonObject o) {
 if(keys.empty()){
	 keys = IV_SETT->get("Keys");
 }

	QJsonArray a = o["keys"].toArray();
	bool sprint = a.contains(getFK("sprint"));

	for(QJsonValue v : a) {
		int k = v.toInt();
		if (k == 0) {
			logW("key parameter is 0");
		} else if (isKey(k, "forw")) {		move(0.0f,   sprint ? 0.5f : 0.05f);
		} else if (isKey(k, "back")) {		move(3.141f, sprint ? 0.5f : 0.05f);
		} else if (isKey(k, "left")) {		move(-1.57f, sprint ? 0.5f : 0.05f);
		} else if (isKey(k, "righ")) {		move(1.57f,  sprint ? 0.5f : 0.05f);
		} else if (isKey(k, "jump")) {		moveU(sprint ? 0.5f : 0.1f);
		} else if (isKey(k, "sneak")) {	moveD(sprint ? 0.5f : 0.1f);
		} else if (isKey(k, "sprint")){
		} else {
			logI(QString("Strange, key is not in keyMap: %1").arg(k));
		}
	}
}

bool MPlayer::isKey(int k, QString v) {
	bool r = false;
	for(QString i : keys.keys()){
		if(keys[i] == v && i == QString::number(k))
			r = true;
	}
	return r;
}

int MPlayer::getFK(QString v) {
	for(QString i : keys.keys()){
		if(keys[i] == v )
			return i.toInt();
	}
	logW("No such key in keyMap: " + v);
	return 0;
}
