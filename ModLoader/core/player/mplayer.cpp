#include <ModLoader/core/player/mplayer.h>


void MPlayer::moveF() { move(   0.0f);}
void MPlayer::moveB() { move( 3.141f);}
void MPlayer::moveL() { move( -1.57f);}
void MPlayer::moveR() { move(  1.57f);}

void MPlayer::move(float r) {
	x = x + cosf(aP + r) * 0.2f;
	z = z + sinf(aP + r) * 0.2f;
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
