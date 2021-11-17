#pragma once

#include <Windows.h>
#include <d2d1.h>
#include <d2d1_1.h>
#pragma comment(lib, "Dwrite")
#pragma comment(lib, "d2d1.lib")
#pragma comment(lib, "windowscodecs.lib")

#include <dwrite.h>
#include "Definitions.h"

class Graphics {
private:
	ID2D1Factory* factory;
	ID2D1HwndRenderTarget* renderTarget;
	ID2D1SolidColorBrush* brush;
	IDWriteFactory* writeFactory;

public:
	Graphics();
	~Graphics();

	bool Init(HWND windowHandle);

	void BeginDraw() {
		renderTarget->BeginDraw();
	}

	void EndDraw() {
		renderTarget->EndDraw();
	}

	ID2D1HwndRenderTarget* GetRenderTarget() {
		return renderTarget;
	}

	IDWriteFactory* GeWriteFactory() {
		return writeFactory;
	}

	void ClearScreen(float r, float g, float b);

	void DrawCircle(float x, float y, float radius, float r, float g, float b, float a);
	void DrawRectangle(float x1, float y1, float x2, float y2, float r, float g, float b, float a);
	void FillRectangle(float x1, float y1, float x2, float y2, float r, float g, float b, float a);
};