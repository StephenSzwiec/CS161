#pragma once
#include "Object_Mobile.h"

class Object_Player : public Object_Mobile
{
public:
	Object_Player(int objectIndex, float velocityx, float velocityy, int x, int y, SpriteSheet* ss, Object_Game** objectArray, float scaleFactor = 1.0f);
	void Setvelocity(int xMod, int yMod);		//Call to change the x,y value of the Player's Ship by the values xMod,yMod
	void AnimateSprite() override;
	void UpdateObjectPosition() override;
};