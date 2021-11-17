#pragma once
#include "Level_Game.h"
#include <Mmsystem.h>
#include <mciapi.h>
//these two headers are already included in the <Windows.h> header
#pragma comment(lib, "Winmm.lib")
#include <list>

class Level_Main : public Level_Game {
private:
	SpriteSheet* infoBox = NULL;

	SpriteSheet* imgShip = NULL;
	SpriteSheet* imgHitbox = NULL;
	SpriteSheet* imgPlayerBullet = NULL;
	SpriteSheet* imgPlayerLaser = NULL;
	SpriteSheet* imgBomb = NULL;

	SpriteSheet* imgExplode = NULL;

	SpriteSheet* imgEFighterRed = NULL;
	SpriteSheet* imgEFighterYellow = NULL;
	SpriteSheet* imgEFighterGreen = NULL;
	SpriteSheet* imgEFighterCyan = NULL;
	SpriteSheet* imgEFighterBlue = NULL;
	SpriteSheet* imgEFighterPurple = NULL;
	SpriteSheet* imgEFighterPink = NULL;

	SpriteSheet* imgEFleaCyan = NULL;
	SpriteSheet* imgERiceRed = NULL;
	SpriteSheet* imgEFleaGreen = NULL;
	SpriteSheet* imgEBallBlue = NULL;
	SpriteSheet* imgERicePurple = NULL;
	SpriteSheet* imgEFleaPink = NULL;

	SpriteSheet* imgEBomber = NULL;
	SpriteSheet* imgEBomb = NULL;

	Object_Text* txtLives;
	Object_Text* txtBombs;
	Object_Text* txtScore;
	Object_Text* txtPoints;
	Object_Text* txtGameMsg;
	Object_Text* txtVictory;
	Object_Text* txtDefeat;
	SpriteSheet* iconBomb;
	SpriteSheet* iconLife;

	//render precedence: eBullets, pHitbox, pShips, pBomb, eShips
	const int pBullets = 100;
	const int eShips = 30;
	const int pBomb = 1;
	const int pShips = 1;
	const int pHitbox = 1;
	const int eBullets = 400;

	unsigned long ticks;

	int pBulletCount;
	bool shooting;
	int nextFireX;
	int nextFireY;
	int shotNumber;

	int pBombCount;
	bool hasBombed;

	int pLifeCount;
	bool isDead;
	int ticksDead;

	int points;

	bool isGameOver;
	bool hasCleaned;

	std::list<Object_Enemy*> spawns;

public:
	void Load() override;
	void UnLoad() override;
	void EndState();
	void Render() override;
	void Update() override;
	long getTicks();
};