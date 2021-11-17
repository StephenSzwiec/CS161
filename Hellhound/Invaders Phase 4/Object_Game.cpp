#include "Object_Game.h"

/*----Public----*/

Object_Game::Object_Game(int objectIndex, int x, int y, SpriteSheet* ss, Object_Game** objectArray, float scaleFactor) {
	this->objectArray = objectArray;
	this->x = float(x);
	this->y = float(y);

	this->ss = ss;
	this->objectIndex = objectIndex;
	this->scaleFactor = scaleFactor;
}

void Object_Game::Update() {
}

void Object_Game::UpdateObjectPosition() {
}

//AnimateSprite is pure virtual

void Object_Game::CollisionCheck() {
}

void Object_Game::Render() {
	UpdateObjectPosition();		//virtual call
	AnimateSprite();			//virtual call (pure)
	CollisionCheck();			//virtual call
}

int Object_Game::GetX() {
	return x;
}

int Object_Game::GetY() {
	return y;
}

float Object_Game::GetWidth() {
	return scaleFactor * ss->Width();
}

float Object_Game::GetHeight() {
	return scaleFactor * ss->Height();
}

//utility functions added to make this a useful class
float Object_Game::getRad(float deg) {
	return deg * PI / 180.0f;
}
float Object_Game::getCenterX() {
	return this->x + (this->GetWidth() / 2.0f);
}

float Object_Game::getCenterY() {
	return this->y + (this->GetHeight() / 2.0f);
}

//angle between two points in radians
double Object_Game::getTheta(double x1, double y1, double x2, double y2) {
	return atan2(y2 - y1, x2 - x1);
}