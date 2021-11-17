#pragma once

#include "Object_Mobile.h"
#include "Object_Explosion.h"
#include "Object_Player.h"
#include <functional>

class Object_Enemy : public Object_Mobile
{
private:
	Object_Player* temp = NULL;
protected:
	SpriteSheet* imgExplode = NULL;
	int spawnTime;
	int health;
	int scoring;
	long elapsedTicks;
	int facing;
	float speed;
	float bulletSpeed;
	long delay;
	std::function<void(Object_Enemy&, float)> funcMove;
	std::function<void(Object_Enemy&, float)> funcShoot;
	std::function<void(Object_Enemy&, float, long)> funcMoveDelay;
	std::function<void(Object_Enemy&, float, long)> funcShootDelay;

public:
	Object_Enemy(int objectIndex, float velocityx, float velocityy, int x, int y, float s, float b, SpriteSheet* ss, SpriteSheet* onExplode, Object_Game** objectArray, long spawn, std::function<void(Object_Enemy&, float)> move, std::function<void(Object_Enemy&, float)> shoot, int health, int points, float scaleFactor);
	Object_Enemy(int objectIndex, float velocityx, float velocityy, int x, int y, float s, float b, long d, SpriteSheet* ss, SpriteSheet* onExplode, Object_Game** objectArray, long spawn, std::function<void(Object_Enemy&, float, long)> move, std::function<void(Object_Enemy&, float, long)> shoot, int health, int points, float scaleFactor);
	void Update() override;
	void AnimateSprite() override;
	void UpdateObjectPosition() override;
	void setVelX(float xIn);
	void setVelY(float yIn);
	void setFacing(int in);
	long getTime();
	long getSpawn();
	void reduceHealth(int damage);
	void setShot(std::function<void(Object_Enemy&, float)> input);
	int getHealth();
	int getPoints();
	void setIndex(int);
};