#include "SpriteSheet.h"

SpriteSheet::SpriteSheet(const wchar_t* filename, Graphics* gfx) {
	this->gfx = gfx;
	bmp = NULL;
	HRESULT hr; //HRESULT for checking errors

	IWICImagingFactory* wicFactory = NULL;
	hr = CoCreateInstance(CLSID_WICImagingFactory,	//CLS ID of the object we're creating
		NULL,										//Not part of an aggragate
		CLSCTX_INPROC_SERVER,						//DLL runs as part of the same process
		IID_IWICImagingFactory,						//Ref to the interface that communicates with the object
		(LPVOID*)&wicFactory);						//The pointer that will contain our factory

	//if (hr==S_OK) if we wanted to check this opened successfully

	IWICBitmapDecoder* wicDecoder = NULL;
	hr = wicFactory->CreateDecoderFromFilename(filename,	//Our file name
		NULL,												//No preferred vendor
		GENERIC_READ,										//Read the file
		WICDecodeMetadataCacheOnLoad,						//Cache on Load (OnDemand works as well)
		&wicDecoder);										//The Decoder we're making

	//Read a frame from an image
	IWICBitmapFrameDecode* wicFrame = NULL;
	if (wicDecoder) {
		hr = wicDecoder->GetFrame(0, &wicFrame); //Which frame? / The frame we're making
	}

	//Create a converter to convert the image to an ID2D1Bitmap
	IWICFormatConverter* wicConverter = NULL;
	hr = wicFactory->CreateFormatConverter(&wicConverter);

	//Setup the converter
	hr = wicConverter->Initialize(wicFrame,				//The frame from above
		GUID_WICPixelFormat32bppPBGRA,					//Pixel Format
		WICBitmapDitherTypeNone,						//Irrelevant
		NULL,											//No pallete needed, irrelevant
		0.0,											//Alpha transparency % irrelevant
		WICBitmapPaletteTypeCustom);					//Irrelevant

	//32bpp -> bits per pixel ; PBGRA -> Packed Blue Green Red Alpha
	//* The irrelevant pieces are for using images that have an indexed pallete
	// Option 2 can be swapped to GUID_WICPixelFormat128bppPBGRAFloat for extra precision

	//Use the converter to crete an d2d1 bitmap
	//(bmp is a member variable)
	hr = gfx->GetRenderTarget()->CreateBitmapFromWicBitmap(wicConverter,	//Our Converter from Above
		NULL,																//D2D1_BITMAP_PROPERIES
		&bmp);																//Destination bmp

	//IWICBitmapFlipRotator *flipRotator = NULL;

	//hr = wicFactory->CreateBitmapFlipRotator(&flipRotator);

	if (wicFactory) wicFactory->Release();
	if (wicDecoder) wicDecoder->Release();
	if (wicConverter) wicConverter->Release();
	if (wicFrame) wicFrame->Release();

	//By default, our sprite is just a single image
	spriteWidth = (int)bmp->GetSize().width;
	spriteHeight = (int)bmp->GetSize().height;
	spritesAcross = 1;

	currentTransform = 0.0f;
}

SpriteSheet::SpriteSheet(const wchar_t* filename, Graphics* gfx, int spriteWidth, int spriteHeight) : SpriteSheet(filename, gfx) {
	this->spriteWidth = spriteWidth;
	this->spriteHeight = spriteHeight;
	this->spritesAcross = (int)(bmp->GetSize().width / spriteWidth);
}

SpriteSheet::~SpriteSheet() {
	if (bmp) bmp->Release();
}

void SpriteSheet::Draw(float x, float y, float scaleFactor) {
	gfx->GetRenderTarget()->DrawBitmap(bmp,													//Bitmap
		D2D1::RectF(x, y, x + (bmp->GetSize().width * scaleFactor), y + (bmp->GetSize().height * scaleFactor)),				//Destination
		1.0f,																				//Opacity 100% = 1.0f
		D2D1_BITMAP_INTERPOLATION_MODE::D2D1_BITMAP_INTERPOLATION_MODE_NEAREST_NEIGHBOR,	//Interpolation (Stretching image - NN is the fastest)
		D2D1::RectF(0.0f, 0.0f, bmp->GetSize().width, bmp->GetSize().height));			//Source Rectangle
}

void SpriteSheet::Draw(int index, float x, float y, float scaleFactor) {
	float left = (float)((index % spritesAcross) * spriteWidth);
	float top = (float)((index / spritesAcross) * spriteHeight);

	D2D_RECT_F src = D2D1::RectF(left, top, left + spriteWidth, top + spriteHeight);

	D2D_RECT_F dst = D2D1::RectF(x, y, x + (spriteWidth * scaleFactor), y + (spriteHeight * scaleFactor));

	gfx->GetRenderTarget()->DrawBitmap(bmp,													//Bitmap
		dst,																				//Destination
		1.0f,																				//Opacity 100% = 1.0f
		D2D1_BITMAP_INTERPOLATION_MODE::D2D1_BITMAP_INTERPOLATION_MODE_NEAREST_NEIGHBOR,	//Interpolation (Stretching image - NN is the fastest)
		src);																				//Source Rectangle
}

void SpriteSheet::Draw(int index, int row, float x, float y, float scaleFactor) {
	float left = (float)((index % spritesAcross) * spriteWidth);
	float top = (float)(row * spriteHeight);

	D2D_RECT_F src = D2D1::RectF(left, top, left + spriteWidth, top + spriteHeight);

	D2D_RECT_F dst = D2D1::RectF(x, y, x + (spriteWidth * scaleFactor), y + (spriteHeight * scaleFactor));

	gfx->GetRenderTarget()->DrawBitmap(bmp,													//Bitmap
		dst,																				//Destination
		1.0f,																				//Opacity 100% = 1.0f
		D2D1_BITMAP_INTERPOLATION_MODE::D2D1_BITMAP_INTERPOLATION_MODE_NEAREST_NEIGHBOR,	//Interpolation (Stretching image - NN is the fastest)
		src);																				//Source Rectangle
}

void SpriteSheet::Transform(D2D1::Matrix3x2F mtx) {
	//gfx->GetRenderTarget()->SetTransform(D2D1::Matrix3x2F::Rotation(transformDegrees, D2D1::Point2F(x, y)));
	gfx->GetRenderTarget()->SetTransform(mtx);
}

int SpriteSheet::Width() {
	return spriteWidth;
}

int SpriteSheet::Height() {
	return spriteHeight;
}