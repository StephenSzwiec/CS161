#include "Object_Bullets.h"

Object_Bullets::Object_Bullets(int objectIndex, int startIndex, int endIndex, float velocityx, float velocityy, int x, int y, SpriteSheet* ss, Object_Game** objectArray, float scaleFactor) : Object_Mobile(objectIndex, velocityx, velocityy, x, y, ss, objectArray, scaleFactor)
{
	this->startIndex = startIndex;
	this->endIndex = endIndex;
	mciSendString("play laser.mp3", NULL, 0, NULL);
}

void Object_Bullets::UpdateObjectPosition()
{
	//simply move the bullet
	x += velocityX;
	y += velocityY;
}

void Object_Bullets::AnimateSprite() {
	ss->Draw(x, y, scaleFactor);
}