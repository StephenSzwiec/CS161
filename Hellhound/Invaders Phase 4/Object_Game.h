#pragma once

#include "SpriteSheet.h"
#include <stdio.h>
#include <wchar.h>
#include <math.h>
#include <limits>

class Object_Game {
protected:
	Object_Game** objectArray;
	int objectIndex;

	SpriteSheet* ss;			//sprite sheet that will represent this object in the game
	float scaleFactor;			//scaleFactor when drawing our spritesheet
	bool isDestroyable;			//Can this object be destroyed by collisions (bullets, ships)

	float x;					//x coordinate for this game object
	float y;					//y coordinate for this game object

public:
	Object_Game(int objectIndex, int x, int y, SpriteSheet* ss, Object_Game** objectArray, float scaleFactor = 1.0f);

	virtual void Update();
	virtual void UpdateObjectPosition();
	virtual void AnimateSprite() = 0;
	virtual void CollisionCheck();

	void Render();
	int GetX();
	int GetY();
	float GetWidth();
	float GetHeight();
	//utility functions to be used somewhat often
	const double PI = 3.14259;
	const double epsilon = std::numeric_limits<double>::lowest();

	float getRad(float);
	float getCenterX();
	float getCenterY();
	double getTheta(double, double, double, double);
};
