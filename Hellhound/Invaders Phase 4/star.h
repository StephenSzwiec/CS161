#pragma once
#include "Graphics.h"

class star
{
public:
	star() {}
	star(int, int, float, Graphics*);
	~star() {}
	int getXPos();
	int getYPos() const;
	void setXPos(int);
	void setYPos(int);
	void addYPos(int);
	void render();

private:
	int xPos;
	int yPos;
	float radius;
	Graphics* gfx;
};
