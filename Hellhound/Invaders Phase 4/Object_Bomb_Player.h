#pragma once
#include "Object_Game.h"
#include <Mmsystem.h>
#include <mciapi.h>
//these two headers are already included in the <Windows.h> header
#pragma comment(lib, "Winmm.lib")

class Object_Bomb_Player : public Object_Game {
protected:
	int speed;					//Speed divisor to slow animation
	int frames;					//Frames in the animation
	int index;					//Index of our sprite animation
	bool destroyNow;
public:
	Object_Bomb_Player(int objectIndex, int x, int y, SpriteSheet* ss, Object_Game** objectArray, int frames, int speed = 1, float scaleFactor = 1.0f);
	void AnimateSprite() override;
	void CollisionCheck() override;
};