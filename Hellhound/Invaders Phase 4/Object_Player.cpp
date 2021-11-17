#include "Object_Player.h"

Object_Player::Object_Player(int objectIndex, float velocityx, float velocityy, int x, int y, SpriteSheet* ss, Object_Game** objectArray, float scaleFactor) : Object_Mobile(objectIndex, velocityx, velocityy, x, y, ss, objectArray, scaleFactor)
{
}

void Object_Player::Setvelocity(int xMod, int yMod) {
	velocityX = xMod;
	velocityY = yMod;
}

void Object_Player::AnimateSprite() {
	ss->Draw(x, y, scaleFactor);
}

void Object_Player::UpdateObjectPosition()
{
	x += velocityX;
	y += velocityY;
	velocityX = velocityY = 0;  // Move once per click
	if (x < 0) x = 0;
	else if (x > SCREENWIDTH - GetWidth()) x = SCREENWIDTH - GetWidth();

	if (y < 0) y = 0;
	else if (y > SCREENHEIGHT - GetHeight()) y = SCREENHEIGHT - GetHeight();
}