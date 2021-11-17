#include "Object_Enemy.h"

Object_Enemy::Object_Enemy(int objectIndex, float velocityx, float velocityy, int x, int y, float s, float b, SpriteSheet* ss, SpriteSheet* onExplode, Object_Game** objectArray, long spawn, std::function<void(Object_Enemy&, float)> move, std::function<void(Object_Enemy&, float)> shoot, int health, int points, float scaleFactor) : Object_Mobile(objectIndex, velocityx, velocityy, x, y, ss, objectArray, scaleFactor)
{
	imgExplode = onExplode;
	this->funcShoot = shoot;
	this->funcMove = move;
	this->speed = s;
	this->bulletSpeed = b;
	this->spawnTime = spawn;
	this->health = health;
	this->scoring = points;
	this->elapsedTicks = 0;
	this->facing = 1;
}

Object_Enemy::Object_Enemy(int objectIndex, float velocityx, float velocityy, int x, int y, float s, float b, long d, SpriteSheet* ss, SpriteSheet* onExplode, Object_Game** objectArray, long spawn, std::function<void(Object_Enemy&, float, long)> move, std::function<void(Object_Enemy&, float, long)> shoot, int health, int points, float scaleFactor) : Object_Mobile(objectIndex, velocityx, velocityy, x, y, ss, objectArray, scaleFactor)
{
	imgExplode = onExplode;
	this->funcShootDelay = shoot;
	this->funcMoveDelay = move;
	this->speed = s;
	this->bulletSpeed = b;
	this->delay = d;
	this->spawnTime = spawn;
	this->health = health;
	this->scoring = points;
	this->elapsedTicks = 0;
	this->facing = 1;
}

void Object_Enemy::Update() {
	this->elapsedTicks++;
	if (funcMove) {
		funcMove(*this, speed);
	}
	else if (funcMoveDelay) {
		funcMoveDelay(*this, speed, delay);
	}
	this->UpdateObjectPosition();
	Object_Player* temp = dynamic_cast<Object_Player*>(objectArray[131]);
	if (temp) {
		if (funcShootDelay) {
			funcShootDelay(*this, bulletSpeed, delay);
		}
		else if (funcShoot) {
			funcShoot(*this, bulletSpeed);
		}
	}
}

void Object_Enemy::UpdateObjectPosition()
{
	x += velocityX;
	y += velocityY;
	if (x < 0) {
		objectArray[objectIndex] = NULL;
	}
	else if (x > SCREENWIDTH) {
		objectArray[objectIndex] = NULL;
	}
	if (y < 0) {
		y = 0;
	}
	else if (y > SCREENHEIGHT) {
		objectArray[objectIndex] = NULL;
	}
}

void Object_Enemy::AnimateSprite() {
	ss->Draw(facing, x, y, scaleFactor);
}

void Object_Enemy::setVelX(float xIn) {
	this->velocityX = xIn;
}

void Object_Enemy::setVelY(float yIn) {
	this->velocityY = yIn;
}

void Object_Enemy::setFacing(int in) {
	facing = in;
}

long Object_Enemy::getTime() {
	return elapsedTicks;
}

long Object_Enemy::getSpawn() {
	return spawnTime;
}

void Object_Enemy::reduceHealth(int damage) {
	this->health = health - damage;
	mciSendString("play hit.mp3", NULL, 0, NULL);
}

void Object_Enemy::setShot(std::function<void(Object_Enemy&, float)> input) {
	this->funcShoot = input;
}

int Object_Enemy::getHealth() {
	return this->health;
}

int Object_Enemy::getPoints() {
	return this->scoring;
}

void Object_Enemy::setIndex(int index) {
	this->objectIndex = index;
}