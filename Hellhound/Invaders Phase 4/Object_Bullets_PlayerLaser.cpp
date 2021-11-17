#include "Object_Bullets_PlayerLaser.h"
#include "Object_Enemy.h"
#include "Object_Game.h"

Object_Bullets_PlayerLaser::Object_Bullets_PlayerLaser(int objectIndex, int startIndex, int endIndex, float velocityx, float velocityy, int x, int y, SpriteSheet* ss, Object_Game** objectArray, float scaleFactor) : Object_Bullets(objectIndex, startIndex, endIndex, velocityx, velocityy, x, y, ss, objectArray, scaleFactor)
{
}

void Object_Bullets_PlayerLaser::CollisionCheck()
{
	if (y < 0) {
		objectArray[objectIndex] = NULL;
		delete this;
		return;
	}

	//create the local rectangle
	RECT r1;
	r1.left = (long)x;
	r1.top = (long)y;
	r1.right = (long)x + GetWidth();
	r1.bottom = (long)y + GetHeight();

	for (int idx = startIndex; idx < endIndex; idx++)
	{
		if (objectArray[idx])
		{
			//only create the second rectangle when another object exists
			RECT r2;
			r2.left = (long)objectArray[idx]->GetX();
			r2.top = (long)objectArray[idx]->GetY();
			r2.right = (long)objectArray[idx]->GetX() + objectArray[idx]->GetWidth();
			r2.bottom = (long)objectArray[idx]->GetY() + objectArray[idx]->GetHeight();

			RECT dest; //not used
			//use the intersect to return a bool
			if (IntersectRect(&dest, &r1, &r2)) {
				Object_Enemy* e1 = dynamic_cast<Object_Enemy*>(objectArray[idx]);
				if (e1) {
					e1->reduceHealth(4);
					objectArray[idx] = e1;
					objectArray[objectIndex] = NULL;
					//delete this;
				}
			}
		}
	}
}