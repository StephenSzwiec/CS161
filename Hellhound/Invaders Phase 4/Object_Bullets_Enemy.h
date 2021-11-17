#pragma once
#include "Object_Bullets.h"
#include <Mmsystem.h>
#include <mciapi.h>
//these two headers are already included in the <Windows.h> header
#pragma comment(lib, "Winmm.lib")
#include "Object_Explosion.h"
#include "Object_Player.h"

class Object_Bullets_Enemy : public Object_Bullets
{
private:
	SpriteSheet* imgExplode = NULL;
public:
	Object_Bullets_Enemy(int objectIndex, float velocityx, float velocityy, int x, int y, SpriteSheet* ss, SpriteSheet* explosions, Object_Game** objectArray, float scaleFactor = 1.0f);
	void  CollisionCheck() override;
};