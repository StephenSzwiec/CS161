#pragma once
#include "Level_Game.h"
#include <Mmsystem.h>
#include <mciapi.h>
//these two headers are already included in the <Windows.h> header
#pragma comment(lib, "Winmm.lib")

class Level_Loading : public Level_Game {
private:
	SpriteSheet* logo;
	SpriteSheet* infoBox;
	SpriteSheet* imgExplained;
	Object_Text* txtGameMsg;
	Object_Text* txtStartingMsg;
	Object_Text* txtLives;
	Object_Text* txtBombs;
	Object_Text* txtScore;
	Object_Text* txtInstruction;
	Object_Text* txtPoints;

	std::clock_t loadTime;

public:
	void Load() override;
	void UnLoad() override;
	void Render() override;
	void Update() override;
};