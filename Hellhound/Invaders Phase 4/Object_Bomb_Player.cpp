#include "Object_Bomb_Player.h"
#include "Object_Bullets_Enemy.h"
#include "Object_Enemy.h"

Object_Bomb_Player::Object_Bomb_Player(int objectIndex, int x, int y, SpriteSheet* ss, Object_Game** objectArray, int frames, int speed, float scaleFactor) : Object_Game(objectIndex, x, y, ss, objectArray, scaleFactor)
{
	this->speed = speed;
	this->frames = frames;
	index = 0;
	destroyNow = false;
}

void Object_Bomb_Player::AnimateSprite()
{
	int aniframe = index++ / speed % frames;
	ss->Draw(aniframe, objectArray[131]->getCenterX() - 370, objectArray[131]->getCenterY() - 573, scaleFactor);
	if (aniframe == frames - 1) {
		objectArray[objectIndex] = NULL;
		destroyNow = true;
	}
}

void Object_Bomb_Player::CollisionCheck() {
	if (this->destroyNow) {
		delete this;
	}
	else {
		for (int idx = 133; idx < 533; idx++) {
			if (objectArray[idx]) {
				delete objectArray[idx];
				objectArray[idx] = NULL;
			}
		}
		for (int idx = 100; idx < 129; idx++) {
			if (objectArray[idx]) {
				Object_Enemy* e1 = dynamic_cast<Object_Enemy*>(objectArray[idx]);
				if (e1) {
					e1->reduceHealth(2);
					objectArray[idx] = e1;
				}
			}
		}
	}
}