#pragma once

#include <wincodec.h> //WIC codec header for decoding image from file
#include <math.h>
#include "Graphics.h" //Includes Windows.h and D2d1.h
#pragma comment(lib, "windowscodecs.lib")

class SpriteSheet {
private:
	Graphics* gfx; //Reference to the Graphics class
	ID2D1Bitmap* bmp; //Bitmap loaded from file

	int spriteWidth, spriteHeight;
	int spritesAcross;

	float currentTransform;

public:
	SpriteSheet(const wchar_t* filename, Graphics* gfx);
	SpriteSheet(const wchar_t* filename, Graphics* gfx, int spriteWidth, int spriteHeight);

	~SpriteSheet();

	Graphics* GetGraphics() {
		return gfx;
	}

	//Draw the Bitmap to the render target
	//Draw the entire bitmap
	void Draw(float x, float y, float scaleFactor = 1.0f);

	//Draw index 'index' of an animation
	void Draw(int index, float x, float y, float scaleFactor = 1.0f);

	//Draw index 'index' of an animation
	void Draw(int index, int row, float x, float y, float scaleFactor = 1.0f);

	//Rotate the image
	//void Transform(float transformDegrees, float x, float y);
	void Transform(D2D1::Matrix3x2F mtx);

	int Width();
	int Height();
};
