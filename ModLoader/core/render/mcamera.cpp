#include "ModLoader/core/render/mcamera.h"
#include <GL/glu.h>

MCamera::MCamera(IBlockPos pos) {
	this->pointer = new QCursor(Qt::CrossCursor);
	this->xP = pos.x();
	this->yP = pos.y();
	this->zP = pos.z();
	this->yaw = 0.0f;
	this->pitch = 0.0f;
	this->xS = 1.0f;
	this->xS = 1.0f;
	this->xS = 1.0f;
}

void MCamera::apply() {
	if(wFocus && (wWidth > 0) && (wHeight > 0)) {
		QPoint pos = pointer->pos();
		pos.setX(pos.x() - wWidth / 2);
		pos.setY(pos.y() - wHeight / 2);

		if (pos.x() != 0) pitch += xSense * pos.x() ;
		if (pos.y() != 0) yaw -=  ySense * pos.y();

		yaw = yaw >  90.0f ?  90.0f : yaw;
		yaw = yaw < -90.0f ? -90.0f : yaw;

		pitch = pitch > 360.0f ? 0.0f : pitch;
		pitch = pitch < 0.0f ? 360.0f : pitch;

		pointer->setPos(wWidth / 2, wHeight / 2);
	}

	float cY = cosf(yaw);
	float sY = sinf(yaw);
	float cP = cosf(pitch);
	float sP = sinf(pitch);

	float xL = xP + cP * cY;
	float yL = yP + sY;
	float zL = zP + sP * cY;

	gluLookAt(xP, yP+1.0f, zP, // Position
	          xL, yL+1.0f, zL, // LookAt
	          0.0f, 1.0f, 0.0f); // Up vector

// ((pitch > 270)||(pitch < 90)) ? yaw : -yaw
//	glRotatef(pitch, 0.0f, 1.0, 0.0f);
//	glRotatef(-yaw, 0.0f, 0.0f, 1.0f);
//	glTranslatef(-xP, -yP, -zP);
}

void MCamera::resize(int w, int h) {
	if ((w > 50) && (h > 50)) {
		this->wWidth = w;
		this->wHeight = h;
		pointer->setPos(wWidth / 2, wHeight / 2);
	}
}