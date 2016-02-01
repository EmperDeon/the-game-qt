#include <ModLoader/core/player/mplayer.h>


void MPlayer::move(float r) {
	x = x + cosf(aP + r) * 0.05f;
	z = z + sinf(aP + r) * 0.05f;
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
