#include "ModLoader/core/render/mcamera.h"
#include <GL/glu.h>
#include <iostream>

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

		if (pos.x() != 0) pitch += xSense * pos.x() ;
		if (pos.y() != 0) yaw -=  ySense * pos.y();

		yaw = yaw >  90.0f ?  90.0f : yaw;
		yaw = yaw < -90.0f ? -90.0f : yaw;


		pointer->setPos(wWidth / 2, wHeight / 2);
	}

//	float cosYaw = cosf(degreesToRadians(yaw));
//	float sinYaw = sinf(degreesToRadians(yaw));
//	float sinPitch = sinf(degreesToRadians(pitch));
//
//	//std::cout << '\n' << pitch << ' ' << sinPitch;
//
//	// calculate lookAt based on new position
//	float xL = xP + cosYaw;
//	float yL = yP + sinPitch;
//	float zL = zP + sinYaw;
//
//	// set the camera
////	glScalef(xS, yS, zS);


	glRotatef(pitch, 0.0f, 1.0, 0.0f);
	glRotatef(-yaw, 0.0f, 0.0f, 1.0f);
	glTranslatef(-xP, -yP, -zP);
}

void MCamera::resize(int w, int h){
	this->wWidth = w;
	this->wHeight = h;
	pointer->setPos(wWidth / 2, wHeight / 2);

	gluLookAt(xP, yP, zP, // Position
	          xP + 1.0f, yP, zP, // LookAt
	          0.0f, 1.0f, 0.0f); // Up vector
}