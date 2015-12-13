#include "ModLoader/core/render/mcamera.h"
#include <GL/glu.h>

MCamera::MCamera(IBlockPos pos) {
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
	float cosYaw = cosf(degreesToRadians(yaw));
	float sinYaw = sinf(degreesToRadians(yaw));
	float sinPitch = sinf(degreesToRadians(pitch));

	// calculate lookAt based on new position
	float xL = xP + cosYaw;
	float yL = yP + sinPitch;
	float zL = zP + sinYaw;

	// set the camera
	glScalef(xS, yS, zS);
	gluLookAt(xP, yP, zP, // Position
	          xL, yL, zL, // LookAt
	          0.0f, 1.0f, 0.0f); // Up vector
}
