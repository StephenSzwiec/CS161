#include "Object_Explosion.h"

Object_Explosion::Object_Explosion(int objectIndex, int x, int y, SpriteSheet* ss, Object_Game** objectArray, int frames, int speed, float scaleFactor) : Object_Game(objectIndex, x, y, ss, objectArray, scaleFactor)
{
	this->speed = speed;
	this->frames = frames;
	index = 0;
	destroyNow = false;
}

void Object_Explosion::AnimateSprite()
{
	int aniframe = index++ / 5 % 30;
	ss->Draw(aniframe, x, y, scaleFactor);
	if (aniframe == frames - 1) {
		objectArray[objectIndex] = NULL;
		destroyNow = true;
	}
}

void Object_Explosion::CollisionCheck() {
	if (this->destroyNow) {
		delete this;
	}
}