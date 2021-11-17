#pragma once
#include "Graphics.h"
#include <corecrt_wstdio.h>

class Object_Text {
	Graphics* gfx = NULL; //Reference to the Graphics class
	IDWriteTextFormat* textFormat = NULL;
	ID2D1SolidColorBrush* brush = NULL;
	D2D1_RECT_F location;

	wchar_t baseText[200];
	const wchar_t* initialValue;

public:
	Object_Text(Graphics* gfx, D2D1_RECT_F location, const wchar_t baseText[], const wchar_t fontName[], float fontSize, D2D1::ColorF::Enum brushColor, float brushAlpha, bool centerH = TRUE, bool centerV = TRUE);
	Object_Text(Graphics* gfx, D2D1_RECT_F location, long input, const wchar_t fontName[], float fontSize, D2D1::ColorF::Enum brushColor, float brushAlpha, bool centerH, bool centerV);
	~Object_Text();
	void RenderText(const wchar_t currentValue[]);
	void RenderText();
};
