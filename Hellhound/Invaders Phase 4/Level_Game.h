#pragma once
#include <time.h>
#include <stdio.h>
#include "Graphics.h"
#include "Object_Text.h"
#include "Object_Game.h"
#include "Object_Player.h"
#include "Object_Enemy.h"
#include "Object_Bullets_Player.h"
#include "Object_Bullets_PlayerLaser.h"
#include "Object_Bullets_Enemy.h"
#include "Object_Bomb_Player.h"
#include <ctime>

class Level_Game {
protected:
	static Graphics* gfx;

	Object_Game** objectArray;
	int objectCount;
public:
	static void Init(Graphics* graphics) {
		gfx = graphics;
	}

	virtual void Load() = 0;
	virtual void UnLoad() = 0;
	virtual void Render() = 0;
	virtual void Update() = 0;
};