#include "Graphics.h"

Graphics::Graphics() {
	factory = NULL;
	renderTarget = NULL;
	brush = NULL;
	writeFactory = NULL;
}

Graphics::~Graphics() {
	if (factory) {
		factory->Release();
	}

	if (renderTarget) {
		renderTarget->Release();
	}

	if (brush) {
		brush->Release();
	}

	if (writeFactory) {
		writeFactory->Release();
	}
}

bool Graphics::Init(HWND windowHandle) {
	HRESULT result = D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &factory);

	if (result != S_OK)
		return false;

	//Get the client window for our application
	RECT rect;
	GetClientRect(windowHandle, &rect);

	result = factory->CreateHwndRenderTarget(D2D1::RenderTargetProperties(), D2D1::HwndRenderTargetProperties(windowHandle, D2D1::SizeU(rect.right, rect.bottom)), &renderTarget);

	if (result != S_OK)
		return false;

	result = renderTarget->CreateSolidColorBrush(D2D1::ColorF(0, 0, 0, 0), &brush);

	if (result != S_OK)
		return false;

	// Create a DirectWrite factory.
	result = DWriteCreateFactory(
		DWRITE_FACTORY_TYPE_SHARED,
		__uuidof(writeFactory),
		reinterpret_cast<IUnknown**>(&writeFactory)
	);

	if (result != S_OK)
		return false;

	return true;
}

void Graphics::ClearScreen(float r, float g, float b) {
	renderTarget->Clear(D2D1::ColorF(r, g, b));
}

void Graphics::DrawCircle(float x, float y, float radius, float r, float g, float b, float a) {
	//update the color of our brush
	brush->SetColor(D2D1::ColorF(r, g, b, a));

	//Circle is an ellipse with both radius values set the same
	renderTarget->DrawEllipse(D2D1::Ellipse(D2D1::Point2F(x, y), radius, radius), brush, 3.0f);
}

void Graphics::DrawRectangle(float x1, float y1, float x2, float y2, float r, float g, float b, float a) {
	//update the color of our brush
	brush->SetColor(D2D1::ColorF(r, g, b, a));

	renderTarget->DrawRectangle(D2D1::RectF(x1, y1, x2, y2), brush, 3.0f);
}

void Graphics::FillRectangle(float x1, float y1, float x2, float y2, float r, float g, float b, float a) {
	//update the color of our brush
	brush->SetColor(D2D1::ColorF(r, g, b, a));

	renderTarget->FillRectangle(D2D1::RectF(x1, y1, x2, y2), brush);
}