#include "star.h"

star::star(int xIn, int yIn, float rad, Graphics* gfx) {
	xPos = xIn;
	yPos = yIn;
	radius = rad;
	this->gfx = gfx;
}

int star::getXPos()
{
	return xPos;
}

int star::getYPos() const
{
	return yPos;
}

void star::setXPos(int xIn)
{
	xPos = xIn;
	return;
}

void star::setYPos(int yIn)
{
	yPos = yIn;
	return;
}

void star::addYPos(int yIn)
{
	yPos += yIn;
	return;
}

void star::render() {
	gfx->Graphics::DrawCircle(xPos, yPos, radius, 255, 255, 255, 255);
}