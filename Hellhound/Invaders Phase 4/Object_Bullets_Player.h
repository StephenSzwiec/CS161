#pragma once
#include "Object_Bullets.h"
#include <Mmsystem.h>
#include <mciapi.h>
//these two headers are already included in the <Windows.h> header
#pragma comment(lib, "Winmm.lib")

class Object_Bullets_Player : public Object_Bullets
{
private:
	SpriteSheet* imgExplode = NULL;
public:
	Object_Bullets_Player(int objectIndex, int startIndex, int endIndex, float velocityx, float velocityy, int x, int y, SpriteSheet* ss, Object_Game** objectArray, float scaleFactor = 1.0f);
	void  CollisionCheck() override;
};