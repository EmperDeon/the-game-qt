#include <ModLoader/core/player/mplayer.h>


void MPlayer::move(float r) {
	x = x + cosf(aP + r) * 0.2f;
	z = z + sinf(aP + r) * 0.2f;
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
 this->cX = qint32(x) / CHUNK_SIZE;
	this->cZ = qint32(z) / CHUNK_SIZE;
}
