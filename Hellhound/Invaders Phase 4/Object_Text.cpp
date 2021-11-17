#include "Object_Text.h"

Object_Text::Object_Text(Graphics* gfx, D2D1_RECT_F location, const wchar_t baseText[], const wchar_t fontName[], float fontSize, D2D1::ColorF::Enum  brushColor, float brushAlpha, bool centerH, bool centerV) {
	this->gfx = gfx;
	wcscpy_s(this->baseText, baseText);
	this->location = location;

	HRESULT result;

	result = gfx->GeWriteFactory()->CreateTextFormat(
		fontName,
		NULL,
		//DWRITE_FONT_WEIGHT_NORMAL,
		DWRITE_FONT_WEIGHT_BOLD,
		DWRITE_FONT_STYLE_NORMAL,
		DWRITE_FONT_STRETCH_NORMAL,
		fontSize,
		L"", //locale
		&textFormat);

	// Center the text horizontally and vertically.
	if (centerH)
		textFormat->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_CENTER);

	if (centerV)
		textFormat->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_CENTER);

	result = gfx->GetRenderTarget()->CreateSolidColorBrush(
		D2D1::ColorF(brushColor, brushAlpha),
		&brush);
}

Object_Text::Object_Text(Graphics* gfx, D2D1_RECT_F location, long input, const wchar_t fontName[], float fontSize, D2D1::ColorF::Enum  brushColor, float brushAlpha, bool centerH, bool centerV) {
	this->gfx = gfx;
	swprintf(this->baseText, 200, L"%09d", input);
	this->location = location;

	HRESULT result;

	result = gfx->GeWriteFactory()->CreateTextFormat(
		fontName,
		NULL,
		//DWRITE_FONT_WEIGHT_NORMAL,
		DWRITE_FONT_WEIGHT_BOLD,
		DWRITE_FONT_STYLE_NORMAL,
		DWRITE_FONT_STRETCH_NORMAL,
		fontSize,
		L"", //locale
		&textFormat);

	// Center the text horizontally and vertically.
	if (centerH)
		textFormat->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_CENTER);

	if (centerV)
		textFormat->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_CENTER);

	result = gfx->GetRenderTarget()->CreateSolidColorBrush(
		D2D1::ColorF(brushColor, brushAlpha),
		&brush);
}

Object_Text::~Object_Text() {
	if (textFormat) textFormat->Release();
	if (brush) brush->Release();
}

void Object_Text::RenderText(const wchar_t currentValue[]) {
	wchar_t* combined = new wchar_t[wcslen(this->baseText) + wcslen(currentValue) + 10];

	wcscpy_s(combined, wcslen(this->baseText) + 1, this->baseText);

	wcscpy_s(combined + wcslen(this->baseText), wcslen(currentValue) + 1, currentValue);

	gfx->GetRenderTarget()->DrawText(
		combined,
		wcslen(combined),
		this->textFormat,
		this->location,
		brush
	);

	delete[] combined;
}

void Object_Text::RenderText() {
	gfx->GetRenderTarget()->DrawText(
		baseText,
		wcslen(baseText),
		this->textFormat,
		this->location,
		brush
	);
}