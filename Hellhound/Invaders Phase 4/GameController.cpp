#include "GameController.h"

Level_Game* GameController::currentLevel;
bool GameController::Loading;

wchar_t GameController::address[64];

void GameController::Init() {
	Loading = true;
	currentLevel = 0;
}

void GameController::LoadInitialLevel(Level_Game* lev) {
	Loading = true;
	currentLevel = lev;
	currentLevel->Load();
	Loading = false;
}

void GameController::SwitchLevel(Level_Game* lev) {
	Loading = true;
	currentLevel->UnLoad();
	lev->Load();
	delete currentLevel;
	currentLevel = lev;
	Loading = false;
}

void GameController::Render() {
	if (Loading) return;
	currentLevel->Render();
}

void GameController::Update() {
	if (Loading) return;
	currentLevel->Update();
}

void GameController::QuitGame() {
	Loading = true;
	currentLevel->UnLoad();
	delete currentLevel;
	PostQuitMessage(0);
}