#pragma once
#include "Object_Mobile.h"

class Object_Bullets : public Object_Mobile
{
protected:
	//Will be used to detect collisions
	int startIndex;
	int endIndex;
public:
	Object_Bullets(int objectIndex, int startIndex, int endIndex, float velocityx, float velocityy, int x, int y, SpriteSheet* ss, Object_Game** objectArray, float scaleFactor = 1.0f);
	void UpdateObjectPosition() override;
	void AnimateSprite() override;
};