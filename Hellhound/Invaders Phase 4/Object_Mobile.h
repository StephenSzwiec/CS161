#pragma once
#include "Object_Game.h"

class Object_Mobile : public Object_Game
{
protected:
	float velocityX;
	float velocityY;
public:
	Object_Mobile(int objectIndex, float velocityx, float velocityy, int x, int y, SpriteSheet* ss, Object_Game** objectArray, float scaleFactor = 1.0f);
	float SwapVelocityX();		//This function will handle the swapping of the x velocity and the value of the y velocity to adjust the y postion

	double angMoveX(double, double);
	double angMoveY(double, double);
};
