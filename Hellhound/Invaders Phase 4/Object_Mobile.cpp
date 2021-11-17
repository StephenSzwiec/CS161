#include "Object_Mobile.h"

Object_Mobile::Object_Mobile(int objectIndex, float velocityx, float velocityy, int x, int y, SpriteSheet* ss, Object_Game** objectArray, float scaleFactor) : Object_Game(objectIndex, x, y, ss, objectArray, scaleFactor)
{
	this->velocityX = velocityx;
	this->velocityY = velocityy;
}

float Object_Mobile::SwapVelocityX()		//This function will handle the swapping of the x velocity and the value of the y velocity to adjust the y postion
{
	velocityX *= -1;
	return velocityY;
}

double Object_Mobile::angMoveX(double rad, double mag) {
	return mag * cos(rad);
}
double Object_Mobile::angMoveY(double rad, double mag) {
	return mag * sin(rad);
}