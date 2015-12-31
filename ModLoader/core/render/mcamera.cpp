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
	if((wWidth > 0) && (wHeight > 0)) {
		QPoint pos = pointer->pos();
		pos.setX(pos.x() - wWidth / 2);
		pos.setY(pos.y() - wHeight / 2);

		if (pos.x() != 0) pitch += (pos.x() > 0) ? xSense : -xSense;
		if (pos.y() != 0) yaw += (pos.y() > 0) ? ySense : -ySense;

		pointer->setPos(wWidth / 2, wHeight / 2);
	}

	float cosYaw = cosf(degreesToRadians(yaw));
	float sinYaw = sinf(degreesToRadians(yaw));
	float sinPitch = sinf(degreesToRadians(pitch));

	// calculate lookAt based on new position
	float xL = xP + cosYaw;
	float yL = yP + sinPitch;
	float zL = zP + sinYaw;

	// set the camera
//	glScalef(xS, yS, zS);
	gluLookAt(xP, yP, zP, // Position
	          xL, yL, zL, // LookAt
	          0.0f, 0.0f, 1.0f); // Up vector
}

void MCamera::resize(int w, int h){
	this->wWidth = w;
	this->wHeight = h;
	pointer->setPos(wWidth / 2, wHeight / 2);
}