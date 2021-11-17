#include "Object_Bullets_Enemy.h"

Object_Bullets_Enemy::Object_Bullets_Enemy(int objectIndex, float velocityx, float velocityy, int x, int y, SpriteSheet* ss, SpriteSheet* explosions, Object_Game** objectArray, float scaleFactor) : Object_Bullets(objectIndex, 132, 132, velocityx, velocityy, x, y, ss, objectArray, scaleFactor)
{
	imgExplode = explosions;
	mciSendString("play noise.mp3", NULL, 0, NULL);
}

void Object_Bullets_Enemy::CollisionCheck()
{
	if (y > SCREENHEIGHT) {
		objectArray[objectIndex] = NULL;
		delete this;
		return;
	}
	if (y < 0) {
		objectArray[objectIndex] = NULL;
		delete this;
		return;
	}
	if (x > SCREENWIDTH) {
		objectArray[objectIndex] = NULL;
		delete this;
		return;
	}
	if (x < 0) {
		objectArray[objectIndex] = NULL;
		delete this;
		return;
	}

	Object_Player* temp = dynamic_cast<Object_Player*>(objectArray[131]);
	if (temp) {
		//create the local rectangle
		RECT r1;
		r1.left = (long)x;
		r1.top = (long)y;
		r1.right = (long)x + GetWidth();
		r1.bottom = (long)y + GetHeight();

		RECT r2;
		r2.left = (long)objectArray[132]->GetX();
		r2.top = (long)objectArray[132]->GetY();
		r2.right = (long)objectArray[132]->GetX() + objectArray[132]->GetWidth();
		r2.bottom = (long)objectArray[132]->GetY() + objectArray[132]->GetHeight();

		RECT dest; //not used
		//use the intersect to return a bool

		if (IntersectRect(&dest, &r1, &r2))
		{
			Object_Explosion* boom = new Object_Explosion(objectIndex, objectArray[132]->GetX() - 25, objectArray[132]->GetY() - 25, imgExplode, objectArray, 30, 5);
			objectArray[131] = boom;  // This will use the ship position for the explosion
			mciSendString("play death.mp3 ", NULL, 0, NULL);
			objectArray[objectIndex] = NULL;
			delete this;  // This will delete the bullet
			return;
		}
	}
}