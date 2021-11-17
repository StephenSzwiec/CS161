#include "GameController.h"
#include "Level_Loading.h"
#include "Level_Main.h"

void Level_Loading::Load() {
	logo = new SpriteSheet(L"Logo.png", gfx);
	infoBox = new SpriteSheet(L"infobox.png", gfx);
	imgExplained = new SpriteSheet(L"Explanation.png", gfx);
	txtGameMsg = new Object_Text(gfx, D2D1::RectF(SCREENWIDTH / 2 - 250, SCREENHEIGHT - 125, SCREENWIDTH / 2 + 250, SCREENHEIGHT), L"Press [z] to begin", L"Consolas", 20.0f, D2D1::ColorF::OrangeRed, 1.0f);
	txtStartingMsg = new Object_Text(gfx, D2D1::RectF(SCREENWIDTH / 2 - 250, SCREENHEIGHT - 75, SCREENWIDTH / 2 + 250, SCREENHEIGHT), L"Move with arrow keys\n [left_shift]focus [z]shoot [x]bomb", L"Consolas", 12.0f, D2D1::ColorF::Gold, 1.0f);
	txtInstruction = new Object_Text(gfx, D2D1::RectF(SCREENWIDTH + 10, 25, SCREENWIDTH + INFOWIDTH - 10, SCREENHEIGHT - 550), L"The Hellhound is heavily armored, but has a vulnerable cockpit: protect this area from enemy fire", L"Consolas", 12.0f, D2D1::ColorF::White, 1.0f);
	txtScore = new Object_Text(gfx, D2D1::RectF(SCREENWIDTH + 10, 150, SCREENWIDTH + 100, SCREENHEIGHT - 250), L"Score : ", L"Consolas", 15.0f, D2D1::ColorF::White, 1.0f);
	txtLives = new Object_Text(gfx, D2D1::RectF(SCREENWIDTH + 10, 275, SCREENWIDTH + 100, SCREENHEIGHT - 250), L"Lives :", L"Consolas", 15.0f, D2D1::ColorF::Gold, 1.0f);
	txtBombs = new Object_Text(gfx, D2D1::RectF(SCREENWIDTH + 10, 350, SCREENWIDTH + 100, SCREENHEIGHT - 250), L"Bombs :", L"Consolas", 15.0f, D2D1::ColorF::Cyan, 1.0f);
	txtPoints = new Object_Text(gfx, D2D1::RectF(SCREENWIDTH + 35, 150, SCREENWIDTH + 225, SCREENHEIGHT - 250), L"000000000", L"Consolas", 15.0f, D2D1::ColorF::White, 1.0f);

	loadTime = clock();
	mciSendString("play TitleLoop.mp3 repeat", NULL, 0, NULL);
}

void Level_Loading::Render() {
	//gfx->ClearScreen(0.0f, 0.0f, 0.0f);

	logo->Draw(0, 0, 1.0f);
	infoBox->Draw(0, SCREENWIDTH + 2, 1.0f);
	clock_t sinceLoadTime = (clock() - loadTime) / CLOCKS_PER_SEC;
	if (sinceLoadTime % 2 == 0) {
		txtGameMsg->RenderText();
	}
	txtStartingMsg->RenderText();
	txtInstruction->RenderText();
	txtScore->RenderText();
	txtLives->RenderText();
	txtBombs->RenderText();
	txtPoints->RenderText();
	imgExplained->Draw(SCREENWIDTH, SCREENHEIGHT - 525);
	if (GetKeyState('Z') & 0x8000) {
		mciSendString("close TitleLoop.mp3", NULL, 0, NULL);
		GameController::SwitchLevel(new Level_Main());
	}
}

void Level_Loading::UnLoad() {
	if (logo) delete logo;
	if (txtGameMsg) delete txtGameMsg;
	if (imgExplained) delete imgExplained;
	if (txtStartingMsg) delete txtStartingMsg;
	if (txtInstruction) delete txtInstruction;
	if (txtScore) delete txtScore;
	if (txtLives) delete txtLives;
	if (txtBombs) delete txtBombs;
	if (txtPoints) delete txtPoints;
}

void Level_Loading::Update() {
}