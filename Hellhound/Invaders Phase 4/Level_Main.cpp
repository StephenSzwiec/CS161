#include "GameController.h"
#include "Level_Main.h"

void Level_Main::Load() {
	//movement types
	auto Move_None = [&](Object_Enemy& e, float foo) {
		e.setVelX(0);
		e.setVelY(0);
	};

	auto Move_Straight = [&](Object_Enemy& e, float speed) {
		e.setVelY(speed);
	};

	auto Move_Sinusoid = [&](Object_Enemy& e, float speed) {
		e.setVelY(speed);
		e.setVelX(speed * 1.5f * cosf(e.getTime() * e.PI / 180.0f));
	};

	auto Move_Curve_Left = [&](Object_Enemy& e, float speed) {
		e.setVelY(speed);
		e.setVelX(pow(speed, 1.25f) * (1 - pow(e.getTime(), 0.15f)));
	};

	auto Move_Curve_Right = [&](Object_Enemy& e, float speed) {
		e.setVelY(speed);
		e.setVelX(-pow(speed, 1.25f) * (1 - pow(e.getTime(), 0.15f)));
	};

	auto Move_Kamikaze = [&](Object_Enemy& e, float speed) {
		if (objectArray[132]) {
			double theta = e.getTheta(e.getCenterX(), e.getCenterY(), objectArray[132]->getCenterX(), objectArray[132]->getCenterY());
			float velX = e.angMoveX(theta, speed);
			e.setVelX(velX);
			float velY = e.angMoveY(theta, speed);
			e.setVelY(velY);

			//change facing based on heading
			if (theta < (-5.0f * e.PI / 6.0f)) {
				e.setFacing(2);
			}
			else if (theta < (-2.0f * e.PI / 3.0f)) {
				e.setFacing(4);
			}
			else if (theta < (-e.PI / 3.0f)) {
				e.setFacing(0);
			}
			else if (theta < (-e.PI / 6.0f)) {
				e.setFacing(5);
			}
			else if (theta < (e.PI / 6.0f)) {
				e.setFacing(3);
			}
			else if (theta < (e.PI / 3.0f)) {
				e.setFacing(7);
			}
			else if (theta < (2.0f * e.PI / 3.0f)) {
				e.setFacing(1);
			}
			else if (theta < (5.0f * e.PI / 6.0f)) {
				e.setFacing(6);
			}
			else {
				e.setFacing(2);
			}
		}
		else {
			Move_None(e, 0);
		}
	};

	auto Move_Delay_Straight = [&](Object_Enemy& e, float speed, long delay) {
		if (e.getTime() < 60) {
			Move_Straight(e, speed);
		}
		else if (e.getTime() < 60 + delay) {
			Move_None(e, speed);
			double theta = e.getTheta(e.getCenterX(), e.getCenterY(), objectArray[132]->GetX(), objectArray[132]->GetY());
			//change facing based on heading
			if (theta < (-5.0f * e.PI / 6.0f)) {
				e.setFacing(2);
			}
			else if (theta < (-2.0f * e.PI / 3.0f)) {
				e.setFacing(4);
			}
			else if (theta < (-e.PI / 3.0f)) {
				e.setFacing(0);
			}
			else if (theta < (-e.PI / 6.0f)) {
				e.setFacing(5);
			}
			else if (theta < (e.PI / 6.0f)) {
				e.setFacing(3);
			}
			else if (theta < (e.PI / 3.0f)) {
				e.setFacing(7);
			}
			else if (theta < (2.0f * e.PI / 3.0f)) {
				e.setFacing(1);
			}
			else if (theta < (5.0f * e.PI / 6.0f)) {
				e.setFacing(6);
			}
			else {
				e.setFacing(2);
			}
		}
		else {
			e.setFacing(1);
			Move_Straight(e, speed);
		}
	};

	auto Move_Delay_Curve_Left = [&](Object_Enemy& e, float speed, long delay) {
		if (e.getTime() < 60) {
			Move_Curve_Left(e, speed);
		}
		else if (e.getTime() < 60 + delay) {
			Move_None(e, speed);
			double theta = e.getTheta(e.getCenterX(), e.getCenterY(), objectArray[132]->GetX(), objectArray[132]->GetY());
			//change facing based on heading
			if (theta < (-5.0f * e.PI / 6.0f)) {
				e.setFacing(2);
			}
			else if (theta < (-2.0f * e.PI / 3.0f)) {
				e.setFacing(4);
			}
			else if (theta < (-e.PI / 3.0f)) {
				e.setFacing(0);
			}
			else if (theta < (-e.PI / 6.0f)) {
				e.setFacing(5);
			}
			else if (theta < (e.PI / 6.0f)) {
				e.setFacing(3);
			}
			else if (theta < (e.PI / 3.0f)) {
				e.setFacing(7);
			}
			else if (theta < (2.0f * e.PI / 3.0f)) {
				e.setFacing(1);
			}
			else if (theta < (5.0f * e.PI / 6.0f)) {
				e.setFacing(6);
			}
			else {
				e.setFacing(2);
			}
		}
		else {
			e.setFacing(1);
			Move_Curve_Left(e, speed);
		}
	};

	auto Move_Delay_Curve_Right = [&](Object_Enemy& e, float speed, long delay) {
		if (e.getTime() < 60) {
			Move_Curve_Right(e, speed);
		}
		else if (e.getTime() < 60 + delay) {
			Move_None(e, speed);
			double theta = e.getTheta(e.getCenterX(), e.getCenterY(), objectArray[132]->GetX(), objectArray[132]->GetY());
			//change facing based on heading
			if (theta < (-5.0f * e.PI / 6.0f)) {
				e.setFacing(2);
			}
			else if (theta < (-2.0f * e.PI / 3.0f)) {
				e.setFacing(4);
			}
			else if (theta < (-e.PI / 3.0f)) {
				e.setFacing(0);
			}
			else if (theta < (-e.PI / 6.0f)) {
				e.setFacing(5);
			}
			else if (theta < (e.PI / 6.0f)) {
				e.setFacing(3);
			}
			else if (theta < (e.PI / 3.0f)) {
				e.setFacing(7);
			}
			else if (theta < (2.0f * e.PI / 3.0f)) {
				e.setFacing(1);
			}
			else if (theta < (5.0f * e.PI / 6.0f)) {
				e.setFacing(6);
			}
			else {
				e.setFacing(2);
			}
		}
		else {
			e.setFacing(1);
			Move_Curve_Right(e, speed);
		}
	};

	//spritesheets
	infoBox = new SpriteSheet(L"infobox.png", gfx);
	imgShip = new SpriteSheet(L"Hellhound.png", gfx);
	imgHitbox = new SpriteSheet(L"hitbox.png", gfx);
	imgPlayerBullet = new SpriteSheet(L"bullet.png", gfx);
	imgPlayerLaser = new SpriteSheet(L"laser2.png", gfx);
	imgBomb = new SpriteSheet(L"bomb3.png", gfx, 740, 1200);
	imgExplode = new SpriteSheet(L"explosion_36_64x64.png", gfx, 64, 64);
	imgEFighterRed = new SpriteSheet(L"Fighter_Red_Spritesheet.png", gfx, 50, 50);
	imgEFighterYellow = new SpriteSheet(L"Fighter_Yellow_Spritesheet.png", gfx, 50, 50);
	imgEFighterGreen = new SpriteSheet(L"Fighter_Green_Spritesheet.png", gfx, 50, 50);
	imgEFighterCyan = new SpriteSheet(L"Fighter_Cyan_Spritesheet.png", gfx, 50, 50);
	imgEFighterBlue = new SpriteSheet(L"Fighter_Blue_Spritesheet.png", gfx, 50, 50);
	imgEFighterPurple = new SpriteSheet(L"Fighter_Purple_Spritesheet.png", gfx, 50, 50);
	imgEFighterPink = new SpriteSheet(L"Fighter_Pink_Spritesheet.png", gfx, 50, 50);
	imgEFleaCyan = new SpriteSheet(L"flea_cyan_small.png", gfx);
	imgERiceRed = new SpriteSheet(L"thickrice_red_small.png", gfx);
	imgEFleaGreen = new SpriteSheet(L"flea_green_small.png", gfx);
	imgEBallBlue = new SpriteSheet(L"plainball_blue_large.png", gfx);
	imgERicePurple = new SpriteSheet(L"thickrice_purple_small.png", gfx);
	imgEFleaPink = new SpriteSheet(L"flea_pink_small.png", gfx);
	imgEBomb = new SpriteSheet(L"eBomb.png", gfx);
	imgEBomber = new SpriteSheet(L"Enemy_Bomber.png", gfx);
	iconLife = new SpriteSheet(L"lifeicon.png", gfx);
	iconBomb = new SpriteSheet(L"bombicon.png", gfx);

	//UI display
	txtScore = new Object_Text(gfx, D2D1::RectF(SCREENWIDTH + 10, 150, SCREENWIDTH + 100, SCREENHEIGHT - 250), L"Score : ", L"Consolas", 15.0f, D2D1::ColorF::White, 1.0f);
	txtLives = new Object_Text(gfx, D2D1::RectF(SCREENWIDTH + 10, 275, SCREENWIDTH + 100, SCREENHEIGHT - 250), L"Lives :", L"Consolas", 15.0f, D2D1::ColorF::Gold, 1.0f);
	txtBombs = new Object_Text(gfx, D2D1::RectF(SCREENWIDTH + 10, 375, SCREENWIDTH + 100, SCREENHEIGHT - 250), L"Bombs :", L"Consolas", 15.0f, D2D1::ColorF::Cyan, 1.0f);
	txtPoints = new Object_Text(gfx, D2D1::RectF(SCREENWIDTH + 35, 150, SCREENWIDTH + 225, SCREENHEIGHT - 250), points, L"Consolas", 15.0f, D2D1::ColorF::White, 1.0f, TRUE, TRUE);
	txtGameMsg = new Object_Text(gfx, D2D1::RectF(SCREENWIDTH / 2 - 250, SCREENHEIGHT - 125, SCREENWIDTH / 2 + 250, SCREENHEIGHT), L"Press [z] to restart \nPress [esc] to exit", L"Consolas", 18.0f, D2D1::ColorF::OrangeRed, 1.0f);
	txtVictory = new Object_Text(gfx, D2D1::RectF(0, 0, SCREENWIDTH, SCREENHEIGHT), L"YOU ARE VICTORIOUS", L"Impact", 24.0f, D2D1::ColorF::Gold, 1.0f);
	txtDefeat = new Object_Text(gfx, D2D1::RectF(0, 0, SCREENWIDTH, SCREENHEIGHT), L"DEFEAT", L"Impact", 24.0f, D2D1::ColorF::Red, 1.0f);

	//shot types
	auto Shot_None = [&](Object_Enemy&, float bar) {
	};

	auto Shot_Straight = [&](Object_Enemy& e, float speed) {
		int side = 0;
		if (e.getTime() % 20 == 0) {
			int enemyBullets = 0;
			for (int x = 133; x < 533; x++)  // Used to count how many bullets are flying
			{
				if (objectArray[x]) enemyBullets++;
			}
			if (enemyBullets < 400) {
				int index = 133;
				while (objectArray[index]) {
					index++;
				}
				Object_Bullets_Enemy* eb = new Object_Bullets_Enemy(index, 0.0f, speed, int(e.GetX() + 5), e.GetY() + 20, imgERiceRed, imgExplode, objectArray, 1.0f);
				if (side == 1) {
					eb = new Object_Bullets_Enemy(index, 0.0f, speed, int(e.GetX() + 5), e.GetY() + 20, imgEFleaCyan, imgExplode, objectArray, 1.0f);
					side = 0;
				}
				else {
					eb = new Object_Bullets_Enemy(index, 0.0f, speed, int(e.GetX() + 35), e.GetY() + 20, imgEFleaCyan, imgExplode, objectArray, 1.0f);
					side = 1;
				}
				objectArray[index] = eb;  // puts the bullet in the open spot in the array.
			}
		}
	};

	auto Shot_Aimed = [&](Object_Enemy& e, float speed) {
		int side = rand() % 2;
		if (e.getTime() < 15) {
			return;
		}
		else if (e.getTime() % 15 == 0) {
			int enemyBullets = 0;
			for (int x = 133; x < 533; x++)  // Used to count how many bullets are flying
			{
				if (objectArray[x]) enemyBullets++;
			}
			if (enemyBullets < 400) {
				int index = 133;
				while (objectArray[index]) {
					index++;
				}
				Object_Bullets_Enemy* eb = new Object_Bullets_Enemy(index, 0.0f, speed, int(e.GetX() + 5), e.GetY() + 20, imgERiceRed, imgExplode, objectArray, 1.0f);
				if (side == 1) {
					double theta = e.getTheta((float(e.GetX()) + 5.0f), (float(e.GetY()) + 20.0f), objectArray[132]->getCenterX(), objectArray[132]->getCenterY());
					if (theta > 0) {
						eb = new Object_Bullets_Enemy(index, e.angMoveX(theta, speed), speed, int(e.GetX() + 5), int(e.GetY() + 20), imgEFleaCyan, imgExplode, objectArray, 1.0f);
					}
					else {
						eb = new Object_Bullets_Enemy(index, e.angMoveX(theta, speed), -speed, int(e.GetX() + 5), int(e.GetY() + 20), imgEFleaCyan, imgExplode, objectArray, 1.0f);
					}
				}
				else {
					double theta = e.getTheta((float(e.GetX()) + 35.0f), (float(e.GetY()) + 20.0f), objectArray[132]->getCenterX(), objectArray[132]->getCenterY());
					if (theta > 0) {
						eb = new Object_Bullets_Enemy(index, e.angMoveX(-theta, speed), speed, int(e.GetX() + 35), int(e.GetY() + 20), imgEFleaCyan, imgExplode, objectArray, 1.0f);
					}
					else {
						eb = new Object_Bullets_Enemy(index, e.angMoveX(-theta, speed), -speed, int(e.GetX() + 35), int(e.GetY() + 20), imgEFleaCyan, imgExplode, objectArray, 1.0f);
					}
				}
				objectArray[index] = eb;  // puts the bullet in the open spot in the array.
			}
		}
	};

	auto Shot_Grape = [&](Object_Enemy& e, float speed) {
		int side = rand() % 2;
		int pelletNum = 5;
		float spread = 1.0f;
		if (e.getTime() < 15) {
			return;
		}
		else if (rand() % 25 == 1) {
			int enemyBullets = 0;
			for (int x = 133; x < 533; x++)  // Used to count how many bullets are flying
			{
				if (objectArray[x]) enemyBullets++;
			}
			if (enemyBullets < 400) {
				for (int i = 0; i < pelletNum; i++) {
					int index = 133;
					while (objectArray[index]) {
						index++;
					}
					if (side == 1) {
						double theta = e.getTheta((float(e.GetX()) + spread), (float(e.GetY()) + 20.0f), objectArray[132]->getCenterX(), objectArray[132]->getCenterY());
						if (theta > 0) {
							Object_Bullets_Enemy* eb = new Object_Bullets_Enemy(index, e.angMoveX(theta + ((((spread * (rand() % 16)) * (rand() % 3) - 1)) * e.PI / 180), speed), e.angMoveY(theta + ((((spread * (rand() % 16)) * (rand() % 3) - 1)) * e.PI / 180), speed + (0.3f * (rand() % 3 - 1))), int(e.GetX() + 5), int(e.GetY() + 20), imgERiceRed, imgExplode, objectArray, 1.0f);
							objectArray[index] = eb;  // puts the bullet in the open spot in the array.
						}
						else {
							Object_Bullets_Enemy* eb = new Object_Bullets_Enemy(index, e.angMoveX(theta + ((((spread * (rand() % 16)) * (rand() % 3) - 1)) * e.PI / 180), speed), -e.angMoveY(theta + ((((spread * (rand() % 16)) * (rand() % 3) - 1)) * e.PI / 180), -speed + (0.3f * (rand() % 3 - 1))), int(e.GetX() + 5), int(e.GetY() + 20), imgERiceRed, imgExplode, objectArray, 1.0f);
							objectArray[index] = eb;  // puts the bullet in the open spot in the array
						}
					}
					else {
						double theta = e.getTheta((float(e.GetX()) + spread), (float(e.GetY()) + 20.0f), objectArray[132]->getCenterX(), objectArray[132]->getCenterY());
						if (theta > 0) {
							Object_Bullets_Enemy* eb = new Object_Bullets_Enemy(index, e.angMoveX(theta + ((((spread * (rand() % 16)) * (rand() % 3) - 1)) * e.PI / 180), speed), e.angMoveY(theta + ((((spread * (rand() % 16)) * (rand() % 3) - 1)) * e.PI / 180), speed + (0.3f * (rand() % 3 - 1))), int(e.GetX() + 35), int(e.GetY() + 20), imgERiceRed, imgExplode, objectArray, 1.0f);
							objectArray[index] = eb;  // puts the bullet in the open spot in the array
						}
						else {
							Object_Bullets_Enemy* eb = new Object_Bullets_Enemy(index, e.angMoveX(theta + ((((spread * (rand() % 16)) * (rand() % 3) - 1)) * e.PI / 180), speed), -e.angMoveY(theta + ((((spread * (rand() % 16)) * (rand() % 3) - 1)) * e.PI / 180), -speed + (0.3f * (rand() % 3 - 1))), int(e.GetX() + 35), int(e.GetY() + 20), imgERiceRed, imgExplode, objectArray, 1.0f);
							objectArray[index] = eb;  // puts the bullet in the open spot in the array.
						}
					}
				}
			}
		}
	};

	auto Shot_Arc = [&](Object_Enemy& e, float speed) {
		int side = rand() % 2;
		int pelletNum = 5;
		if (e.getTime() < 15) {
			return;
		}
		else if (e.getTime() % 30 == 0) {
			int enemyBullets = 0;
			for (int x = 133; x < 533; x++)  // Used to count how many bullets are flying
			{
				if (objectArray[x]) enemyBullets++;
			}
			if (enemyBullets < 400) {
				for (int i = 0; i < pelletNum; i++) {
					int index = 133;
					while (objectArray[index]) {
						index++;
					}
					if (side == 1) {
						double theta = e.getTheta((float(e.GetX())), (float(e.GetY()) + 20.0f), objectArray[132]->getCenterX(), objectArray[132]->getCenterY()) + (2 * (i - 3) * e.PI / 180.0f);
						if (theta > 0) {
							Object_Bullets_Enemy* eb = new Object_Bullets_Enemy(index, e.angMoveX(theta, speed), e.angMoveY(theta, speed), int(e.GetX() + 5), int(e.GetY() + 20), imgEFleaGreen, imgExplode, objectArray, 1.0f);
							objectArray[index] = eb;  // puts the bullet in the open spot in the array.
						}
						else {
							Object_Bullets_Enemy* eb = new Object_Bullets_Enemy(index, e.angMoveX(theta, speed), e.angMoveY(theta, -speed), int(e.GetX() + 5), int(e.GetY() + 20), imgEFleaGreen, imgExplode, objectArray, 1.0f);
							objectArray[index] = eb;  // puts the bullet in the open spot in the array.
						}
					}
					else {
						double theta = e.getTheta((float(e.GetX())), (float(e.GetY()) + 20.0f), objectArray[132]->getCenterX(), objectArray[132]->getCenterY()) + (2 * (i - 3) * e.PI / 180.0f);
						if (theta > 0) {
							Object_Bullets_Enemy* eb = new Object_Bullets_Enemy(index, e.angMoveX(theta, speed), e.angMoveY(theta, speed), int(e.GetX() + 35), int(e.GetY() + 20), imgEFleaGreen, imgExplode, objectArray, 1.0f);
							objectArray[index] = eb;  // puts the bullet in the open spot in the array.
						}
						else {
							Object_Bullets_Enemy* eb = new Object_Bullets_Enemy(index, e.angMoveX(theta, speed), e.angMoveY(theta, -speed), int(e.GetX() + 35), int(e.GetY() + 20), imgEFleaGreen, imgExplode, objectArray, 1.0f);
							objectArray[index] = eb;  // puts the bullet in the open spot in the array.
						}
					}
				}
			}
		}
	};

	auto Shot_Circle = [&](Object_Enemy& e, float speed) {
		int pelletNum = 20;
		if (e.getTime() < 15) {
			return;
		}
		else if (e.getTime() % 60 == 0) {
			int enemyBullets = 0;
			for (int x = 133; x < 533; x++)  // Used to count how many bullets are flying
			{
				if (objectArray[x]) enemyBullets++;
			}
			if (enemyBullets < 400) {
				for (int i = 0; i < pelletNum; i++) {
					int index = 133;
					while (objectArray[index]) {
						index++;
					}
					double theta = e.getTheta((float(e.GetX()) + 35.0f), (float(e.GetY()) + 10.0f), objectArray[132]->getCenterX(), objectArray[132]->getCenterY());
					if (theta > 0) {
						Object_Bullets_Enemy* eb = new Object_Bullets_Enemy(index, e.angMoveX(theta + ((i * 18) * e.PI / 180.0f), speed), e.angMoveY(theta + ((i * 18) * e.PI / 180.0f), speed), int(e.GetX() + 35), int(e.GetY() + 10), imgEBallBlue, imgExplode, objectArray, 1.0f);
						objectArray[index] = eb;  // puts the bullet in the open spot in the array.
					}
					else {
						Object_Bullets_Enemy* eb = new Object_Bullets_Enemy(index, e.angMoveX(theta + ((i * 18) * e.PI / 180.0f), speed), -e.angMoveY(theta + ((i * 18) * e.PI / 180.0f), -speed), int(e.GetX() + 35), int(e.GetY() + 10), imgEBallBlue, imgExplode, objectArray, 1.0f);
						objectArray[index] = eb;  // puts the bullet in the open spot in the array.
					}
				}
			}
		}
		else if (e.getTime() % 30 == 0) {
			int enemyBullets = 0;
			for (int x = 133; x < 533; x++)  // Used to count how many bullets are flying
			{
				if (objectArray[x]) enemyBullets++;
			}
			if (enemyBullets < 400) {
				for (int i = 0; i < pelletNum; i++) {
					int index = 133;
					while (objectArray[index]) {
						index++;
					}
					double theta = e.getTheta((float(e.GetX()) + 35.0f), (float(e.GetY()) + 10.0f), objectArray[132]->getCenterX(), objectArray[132]->getCenterY());
					Object_Bullets_Enemy* eb = new Object_Bullets_Enemy(index, 0.0f, speed, int(e.GetX() + 5), e.GetY() + 20, imgERiceRed, imgExplode, objectArray, 1.0f);
					if (theta > 0) {
						Object_Bullets_Enemy* eb = new Object_Bullets_Enemy(index, e.angMoveX(theta + ((i * 18) * e.PI / 180.0f), speed), e.angMoveY(theta + ((i * 18) * e.PI / 180.0f), speed), int(e.GetX() + 35), int(e.GetY() + 10), imgEBallBlue, imgExplode, objectArray, 1.0f);
					}
					else {
						Object_Bullets_Enemy* eb = new Object_Bullets_Enemy(index, e.angMoveX(theta + ((i * 18) * e.PI / 180.0f), speed), -e.angMoveY(theta + ((i * 18) * e.PI / 180.0f), speed), int(e.GetX() + 35), int(e.GetY() + 10), imgEBallBlue, imgExplode, objectArray, 1.0f);
					}
					objectArray[index] = eb;  // puts the bullet in the open spot in the array.
				}
			}
		}
	};

	auto Shot_Scatter = [&](Object_Enemy& e, float speed) {
		int pelletNum = 20;
		float spread = 0.5f;
		if (e.getTime() < 15) {
			return;
		}
		else if (e.getTime() % 45 == 0) {
			int enemyBullets = 0;
			for (int x = 133; x < 533; x++)  // Used to count how many bullets are flying
			{
				if (objectArray[x]) enemyBullets++;
			}
			if (enemyBullets < 400) {
				for (int i = 0; i < pelletNum; i++) {
					int index = 133;
					while (objectArray[index]) {
						index++;
					}
					double theta = e.getTheta((float(e.GetX()) + 5.0f), (float(e.GetY()) + 10.0f), objectArray[132]->getCenterX(), objectArray[132]->getCenterY());
					Object_Bullets_Enemy* eb = new Object_Bullets_Enemy(index, e.angMoveX(theta + ((i * 18) * e.PI / 180.0f) + ((((spread * (rand() % 16)) * (rand() % 3) - 1)) * e.PI / 180), speed), e.angMoveY(theta + ((i * 18) * e.PI / 180.0f) + ((((spread * (rand() % 16)) * (rand() % 3) - 1)) * e.PI / 180), speed) + (speed * 0.5F), int(e.GetX() + 5), int(e.GetY() + 10), imgERicePurple, imgExplode, objectArray, 1.0f);
					objectArray[index] = eb;  // puts the bullet in the open spot in the array.
				}
			}
		}
		else if (e.getTime() % 30 == 0) {
			int enemyBullets = 0;
			for (int x = 133; x < 533; x++)  // Used to count how many bullets are flying
			{
				if (objectArray[x]) enemyBullets++;
			}
			if (enemyBullets < 400) {
				for (int i = 0; i < pelletNum; i++) {
					int index = 133;
					while (objectArray[index]) {
						index++;
					}
					double theta = e.getTheta((float(e.GetX()) + 35.0f), (float(e.GetY()) + 10.0f), objectArray[132]->getCenterX(), objectArray[132]->getCenterY());
					Object_Bullets_Enemy* eb = new Object_Bullets_Enemy(index, e.angMoveX(theta + ((i * 18) * e.PI / 180.0f) + ((((spread * (rand() % 16)) * (rand() % 3) - 1)) * e.PI / 180), speed), e.angMoveY(theta + ((i * 18) * e.PI / 180.0f) + ((((spread * (rand() % 16)) * (rand() % 3) - 1)) * e.PI / 180), speed) + (speed * 0.5F), int(e.GetX() + 35), int(e.GetY() + 10), imgERicePurple, imgExplode, objectArray, 1.0f);
					objectArray[index] = eb;  // puts the bullet in the open spot in the array.
				}
			}
		}
	};

	auto Shot_Spiral = [&](Object_Enemy& e, float speed) {
		if (e.getTime() < 15) {
			return;
		}
		else if (e.getTime() % 2 == 0) {
			int enemyBullets = 0;
			for (int x = 133; x < 533; x++)  // Used to count how many bullets are flying
			{
				if (objectArray[x]) enemyBullets++;
			}
			if (enemyBullets < 400) {
				int index = 133;
				while (objectArray[index]) {
					index++;
				}
				Object_Bullets_Enemy* eb = new Object_Bullets_Enemy(index, e.angMoveX(90.0f * e.getTime(), speed), e.angMoveY(90.0f * e.getTime(), speed), e.getCenterX(), e.getCenterY(), imgEFleaPink, imgExplode, objectArray, 1.0f);
				objectArray[index] = eb;
			}
		}
	};

	auto Shot_Delay_Aimed = [&](Object_Enemy& e, float speed, long delay) {
		if (e.getTime() < 60) {
			Shot_None(e, speed);
		}
		else if (e.getTime() < 60 + delay) {
			if (e.getTime() % 15 == 0) {
				int side = rand() % 2;
				int enemyBullets = 0;
				double theta = 0;
				for (int x = 133; x < 533; x++)  // Used to count how many bullets are flying
				{
					if (objectArray[x]) enemyBullets++;
				}
				if (enemyBullets < 400) {
					int index = 133;
					while (objectArray[index]) {
						index++;
					}
					Object_Bullets_Enemy* eb = new Object_Bullets_Enemy(index, 0.0f, speed, int(e.GetX() + 5), e.GetY() + 20, imgERiceRed, imgExplode, objectArray, 1.0f);
					if (side == 1) {
						double theta = e.getTheta((float(e.GetX()) + 5.0f), (float(e.GetY()) + 20.0f), objectArray[132]->getCenterX(), objectArray[132]->getCenterY());
						if (theta > 0) {
							eb = new Object_Bullets_Enemy(index, e.angMoveX(theta, speed), speed, int(e.GetX() + 5), int(e.GetY() + 20), imgEFleaCyan, imgExplode, objectArray, 1.0f);
						}
						else {
							eb = new Object_Bullets_Enemy(index, e.angMoveX(theta, speed), -speed, int(e.GetX() + 5), int(e.GetY() + 20), imgEFleaCyan, imgExplode, objectArray, 1.0f);
						}
					}
					else {
						double theta = e.getTheta((float(e.GetX()) + 35.0f), (float(e.GetY()) + 20.0f), objectArray[132]->getCenterX(), objectArray[132]->getCenterY());
						if (theta > 0) {
							eb = new Object_Bullets_Enemy(index, e.angMoveX(-theta, speed), speed, int(e.GetX() + 35), int(e.GetY() + 20), imgEFleaCyan, imgExplode, objectArray, 1.0f);
						}
						else {
							eb = new Object_Bullets_Enemy(index, e.angMoveX(-theta, speed), -speed, int(e.GetX() + 35), int(e.GetY() + 20), imgEFleaCyan, imgExplode, objectArray, 1.0f);
						}
					}
					objectArray[index] = eb;  // puts the bullet in the open spot in the array.
				}
			}
		}
		else {
			e.setFacing(1);
			Shot_None(e, speed);
		}
	};

	auto Shot_Delay_Grape = [&](Object_Enemy& e, float speed, long delay) {
		if (e.getTime() < 60) {
			Shot_None(e, speed);
		}
		else if (e.getTime() < 60 + delay) {
			if (rand() % 25 == 1) {
				int side = rand() % 2;
				int pelletNum = 5;
				float spread = 1.0f;
				int enemyBullets = 0;
				for (int x = 133; x < 533; x++)  // Used to count how many bullets are flying
				{
					if (objectArray[x]) enemyBullets++;
				}
				if (enemyBullets < 400) {
					for (int i = 0; i < pelletNum; i++) {
						int index = 133;
						while (objectArray[index]) {
							index++;
						}
						if (side == 1) {
							double theta = e.getTheta((float(e.GetX()) + spread), (float(e.GetY()) + 20.0f), objectArray[132]->getCenterX(), objectArray[132]->getCenterY());
							if (theta > 0) {
								Object_Bullets_Enemy* eb = new Object_Bullets_Enemy(index, e.angMoveX(theta + ((((spread * (rand() % 16)) * (rand() % 3) - 1)) * e.PI / 180), speed), e.angMoveY(theta + ((((spread * (rand() % 16)) * (rand() % 3) - 1)) * e.PI / 180), speed + (0.3f * (rand() % 3 - 1))), int(e.GetX() + 5), int(e.GetY() + 20), imgERiceRed, imgExplode, objectArray, 1.0f);
								objectArray[index] = eb;  // puts the bullet in the open spot in the array.
							}
							else {
								Object_Bullets_Enemy* eb = new Object_Bullets_Enemy(index, e.angMoveX(theta + ((((spread * (rand() % 16)) * (rand() % 3) - 1)) * e.PI / 180), speed), -e.angMoveY(theta + ((((spread * (rand() % 16)) * (rand() % 3) - 1)) * e.PI / 180), -speed + (0.3f * (rand() % 3 - 1))), int(e.GetX() + 5), int(e.GetY() + 20), imgERiceRed, imgExplode, objectArray, 1.0f);
								objectArray[index] = eb;  // puts the bullet in the open spot in the array.
							}
						}
						else {
							double theta = e.getTheta((float(e.GetX()) + spread), (float(e.GetY()) + 20.0f), objectArray[132]->getCenterX(), objectArray[132]->getCenterY());
							if (theta > 0) {
								Object_Bullets_Enemy* eb = new Object_Bullets_Enemy(index, e.angMoveX(theta + ((((spread * (rand() % 16)) * (rand() % 3) - 1)) * e.PI / 180), speed), e.angMoveY(theta + ((((spread * (rand() % 16)) * (rand() % 3) - 1)) * e.PI / 180), speed + (0.3f * (rand() % 3 - 1))), int(e.GetX() + 35), int(e.GetY() + 20), imgERiceRed, imgExplode, objectArray, 1.0f);
								objectArray[index] = eb;  // puts the bullet in the open spot in the array.
							}
							else {
								Object_Bullets_Enemy* eb = new Object_Bullets_Enemy(index, e.angMoveX(theta + ((((spread * (rand() % 16)) * (rand() % 3) - 1)) * e.PI / 180), speed), -e.angMoveY(theta + ((((spread * (rand() % 16)) * (rand() % 3) - 1)) * e.PI / 180), -speed + (0.3f * (rand() % 3 - 1))), int(e.GetX() + 35), int(e.GetY() + 20), imgERiceRed, imgExplode, objectArray, 1.0f);
								objectArray[index] = eb;  // puts the bullet in the open spot in the array.
							}
						}
					}
				}
			}
		}
		else {
			Shot_None(e, speed);
		}
	};

	auto Shot_Delay_Arc = [&](Object_Enemy& e, float speed, long delay) {
		if (e.getTime() < 60) {
			Shot_None(e, speed);
		}
		else if (e.getTime() < 60 + delay) {
			if (e.getTime() % 30 == 0) {
				int side = rand() % 2;
				int pelletNum = 5;
				int enemyBullets = 0;
				for (int x = 133; x < 533; x++)  // Used to count how many bullets are flying
				{
					if (objectArray[x]) enemyBullets++;
				}
				if (enemyBullets < 400) {
					for (int i = 0; i < pelletNum; i++) {
						int index = 133;
						while (objectArray[index]) {
							index++;
						}
						if (side == 1) {
							double theta = e.getTheta((float(e.GetX())), (float(e.GetY()) + 20.0f), objectArray[132]->getCenterX(), objectArray[132]->getCenterY()) + (2 * (i - 3) * e.PI / 180.0f);
							if (theta > 0) {
								Object_Bullets_Enemy* eb = new Object_Bullets_Enemy(index, e.angMoveX(theta, speed), e.angMoveY(theta, speed), int(e.GetX() + 5), int(e.GetY() + 20), imgEFleaGreen, imgExplode, objectArray, 1.0f);
								objectArray[index] = eb;  // puts the bullet in the open spot in the array.
							}
							else {
								Object_Bullets_Enemy* eb = new Object_Bullets_Enemy(index, e.angMoveX(theta, speed), -e.angMoveY(theta, -speed), int(e.GetX() + 5), int(e.GetY() + 20), imgEFleaGreen, imgExplode, objectArray, 1.0f);
								objectArray[index] = eb;  // puts the bullet in the open spot in the array.
							}
						}
						else {
							double theta = e.getTheta((float(e.GetX())), (float(e.GetY()) + 20.0f), objectArray[132]->getCenterX(), objectArray[132]->getCenterY()) + (2 * (i - 3) * e.PI / 180.0f);
							if (theta > 0) {
								Object_Bullets_Enemy* eb = new Object_Bullets_Enemy(index, e.angMoveX(theta, speed), e.angMoveY(theta, speed), int(e.GetX() + 35), int(e.GetY() + 20), imgEFleaGreen, imgExplode, objectArray, 1.0f);
								objectArray[index] = eb;  // puts the bullet in the open spot in the array.
							}
							else {
								Object_Bullets_Enemy* eb = new Object_Bullets_Enemy(index, e.angMoveX(theta, speed), -e.angMoveY(theta, -speed), int(e.GetX() + 35), int(e.GetY() + 20), imgEFleaGreen, imgExplode, objectArray, 1.0f);
								objectArray[index] = eb;  // puts the bullet in the open spot in the array.
							}
						}
					}
				}
			}
		}
		else {
			Shot_None(e, speed);
		}
	};

	auto Shot_Delay_Circle = [&](Object_Enemy& e, float speed, long delay) {
		if (e.getTime() < 60) {
			Shot_None(e, speed);
		}
		else if (e.getTime() < 60 + delay) {
			int pelletNum = 20;
			if (e.getTime() % 120 == 0) {
				int enemyBullets = 0;
				for (int x = 133; x < 533; x++)  // Used to count how many bullets are flying
				{
					if (objectArray[x]) enemyBullets++;
				}
				if (enemyBullets < 400) {
					for (int i = 0; i < pelletNum; i++) {
						int index = 133;
						while (objectArray[index]) {
							index++;
						}
						double theta = e.getTheta((float(e.GetX()) + 5.0f), (float(e.GetY()) + 10.0f), objectArray[132]->getCenterX(), objectArray[132]->getCenterY());
						if (theta > 0) {
							Object_Bullets_Enemy* eb = new Object_Bullets_Enemy(index, e.angMoveX(theta + ((i * 18) * e.PI / 180.0f), speed), e.angMoveY(theta + ((i * 18) * e.PI / 180.0f), speed), int(e.GetX() + 35), int(e.GetY() + 10), imgEBallBlue, imgExplode, objectArray, 1.0f);
							objectArray[index] = eb;  // puts the bullet in the open spot in the array.
						}
						else {
							Object_Bullets_Enemy* eb = new Object_Bullets_Enemy(index, e.angMoveX(theta + ((i * 18) * e.PI / 180.0f), speed), -e.angMoveY(theta + ((i * 18) * e.PI / 180.0f), -speed), int(e.GetX() + 35), int(e.GetY() + 10), imgEBallBlue, imgExplode, objectArray, 1.0f);
							objectArray[index] = eb;  // puts the bullet in the open spot in the array.
						}
					}
				}
			}
			else if (e.getTime() % 60 == 0) {
				int enemyBullets = 0;
				for (int x = 133; x < 533; x++)  // Used to count how many bullets are flying
				{
					if (objectArray[x]) enemyBullets++;
				}
				if (enemyBullets < 400) {
					for (int i = 0; i < pelletNum; i++) {
						int index = 133;
						while (objectArray[index]) {
							index++;
						}
						double theta = e.getTheta((float(e.GetX()) + 35.0f), (float(e.GetY()) + 10.0f), objectArray[132]->getCenterX(), objectArray[132]->getCenterY());
						if (theta > 0) {
							Object_Bullets_Enemy* eb = new Object_Bullets_Enemy(index, e.angMoveX(theta + ((i * 18) * e.PI / 180.0f), speed), e.angMoveY(theta + ((i * 18) * e.PI / 180.0f), speed), int(e.GetX() + 35), int(e.GetY() + 10), imgEBallBlue, imgExplode, objectArray, 1.0f);
							objectArray[index] = eb;  // puts the bullet in the open spot in the array.
						}
						else {
							Object_Bullets_Enemy* eb = new Object_Bullets_Enemy(index, e.angMoveX(theta + ((i * 18) * e.PI / 180.0f), speed), -e.angMoveY(theta + ((i * 18) * e.PI / 180.0f), speed), int(e.GetX() + 35), int(e.GetY() + 10), imgEBallBlue, imgExplode, objectArray, 1.0f);
							objectArray[index] = eb;  // puts the bullet in the open spot in the array.
						}
					}
				}
			}
		}
		else {
			Shot_None(e, speed);
		}
	};

	auto Shot_Delay_Scatter = [&](Object_Enemy& e, float speed, long delay) {
		if (e.getTime() < 60) {
			Shot_None(e, speed);
		}
		else if (e.getTime() < (60 + delay)) {
			int pelletNum = 20;
			float spread = 0.5f;
			if (e.getTime() < 15) {
				return;
			}
			else if (e.getTime() % 60 == 0) {
				int enemyBullets = 0;
				for (int x = 133; x < 533; x++)  // Used to count how many bullets are flying
				{
					if (objectArray[x]) enemyBullets++;
				}
				if (enemyBullets < 400) {
					for (int i = 0; i < pelletNum; i++) {
						int index = 133;
						while (objectArray[index]) {
							index++;
						}
						double theta = e.getTheta((float(e.GetX()) + 5.0f), (float(e.GetY()) + 10.0f), objectArray[132]->getCenterX(), objectArray[132]->getCenterY());
						Object_Bullets_Enemy* eb = new Object_Bullets_Enemy(index, e.angMoveX(theta + ((i * 18) * e.PI / 180.0f) + ((((spread * (rand() % 16)) * (rand() % 3) - 1)) * e.PI / 180), speed), e.angMoveY(theta + ((i * 18) * e.PI / 180.0f) + ((((spread * (rand() % 16)) * (rand() % 3) - 1)) * e.PI / 180), speed) + (speed * 0.5F), int(e.GetX() + 5), int(e.GetY() + 10), imgERicePurple, imgExplode, objectArray, 1.0f);
						objectArray[index] = eb;  // puts the bullet in the open spot in the array.
					}
				}
			}
			else if (e.getTime() % 30 == 0) {
				int enemyBullets = 0;
				for (int x = 133; x < 533; x++)  // Used to count how many bullets are flying
				{
					if (objectArray[x]) enemyBullets++;
				}
				if (enemyBullets < 400) {
					for (int i = 0; i < pelletNum; i++) {
						int index = 133;
						while (objectArray[index]) {
							index++;
						}
						double theta = e.getTheta((float(e.GetX()) + 35.0f), (float(e.GetY()) + 10.0f), objectArray[132]->getCenterX(), objectArray[132]->getCenterY());
						Object_Bullets_Enemy* eb = new Object_Bullets_Enemy(index, e.angMoveX(theta + ((i * 18) * e.PI / 180.0f) + ((((spread * (rand() % 16)) * (rand() % 3) - 1)) * e.PI / 180), speed), e.angMoveY(theta + ((i * 18) * e.PI / 180.0f) + ((((spread * (rand() % 16)) * (rand() % 3) - 1)) * e.PI / 180), speed) + (speed * 0.5F), int(e.GetX() + 35), int(e.GetY() + 10), imgERicePurple, imgExplode, objectArray, 1.0f);
						objectArray[index] = eb;  // puts the bullet in the open spot in the array.
					}
				}
			}
		}
		else {
			Shot_None(e, speed);
		}
	};

	auto Shot_Delay_Spiral = [&](Object_Enemy& e, float speed, long delay) {
		if (e.getTime() < 60) {
			Shot_None(e, speed);
		}
		else if (e.getTime() < 60 + delay) {
			if (e.getTime() % 2 == 0) {
				int enemyBullets = 0;
				for (int x = 133; x < 533; x++)  // Used to count how many bullets are flying
				{
					if (objectArray[x]) enemyBullets++;
				}
				if (enemyBullets < 400) {
					int index = 133;
					while (objectArray[index]) {
						index++;
					}
					Object_Bullets_Enemy* eb = new Object_Bullets_Enemy(index, e.angMoveX(90.0f * e.getTime(), speed), e.angMoveY(90.0f * e.getTime(), speed), e.getCenterX(), e.getCenterY(), imgEFleaPink, imgExplode, objectArray, 1.0f);
					objectArray[index] = eb;
				}
			}
		}
		else {
			e.setShot(Shot_None);
		}
	};

	auto Shot_Delay_PartingAimed = [&](Object_Enemy& e, float speed, long delay) {
		if (e.getTime() < 60) {
			Shot_None(e, speed);
		}
		else if (e.getTime() < 60 + delay) {
			if (e.getTime() % 15 == 0) {
				int side = rand() % 2;
				int enemyBullets = 0;
				double theta = 0;
				for (int x = 133; x < 533; x++)  // Used to count how many bullets are flying
				{
					if (objectArray[x]) enemyBullets++;
				}
				if (enemyBullets < 400) {
					int index = 133;
					while (objectArray[index]) {
						index++;
					}
					if (side == 1) {
						double theta = e.getTheta((float(e.GetX()) + 5.0f), (float(e.GetY()) + 20.0f), objectArray[132]->getCenterX(), objectArray[132]->getCenterY());
						if (theta > 0) {
							Object_Bullets_Enemy* eb = new Object_Bullets_Enemy(index, e.angMoveX(theta, speed), speed, int(e.GetX() + 5), int(e.GetY() + 20), imgEFleaCyan, imgExplode, objectArray, 1.0f);
							objectArray[index] = eb;  // puts the bullet in the open spot in the array
						}
						else {
							Object_Bullets_Enemy* eb = new Object_Bullets_Enemy(index, e.angMoveX(theta, speed), -speed, int(e.GetX() + 5), int(e.GetY() + 20), imgEFleaCyan, imgExplode, objectArray, 1.0f);
							objectArray[index] = eb;  // puts the bullet in the open spot in the array.
						}
					}
					else {
						double theta = e.getTheta((float(e.GetX()) + 35.0f), (float(e.GetY()) + 20.0f), objectArray[132]->getCenterX(), objectArray[132]->getCenterY());
						if (theta > 0) {
							Object_Bullets_Enemy* eb = new Object_Bullets_Enemy(index, e.angMoveX(-theta, speed), speed, int(e.GetX() + 35), int(e.GetY() + 20), imgEFleaCyan, imgExplode, objectArray, 1.0f);
							objectArray[index] = eb;  // puts the bullet in the open spot in the array.
						}
						else {
							Object_Bullets_Enemy* eb = new Object_Bullets_Enemy(index, e.angMoveX(-theta, speed), -speed, int(e.GetX() + 35), int(e.GetY() + 20), imgEFleaCyan, imgExplode, objectArray, 1.0f);
							objectArray[index] = eb;  // puts the bullet in the open spot in the array.
						}
					}
				}
			}
		}
	};

	auto Shot_Delay_PartingGrape = [&](Object_Enemy& e, float speed, long delay) {
		if (e.getTime() < 60) {
			Shot_None(e, speed);
		}
		else if (e.getTime() < 60 + delay) {
			if (rand() % 25 == 1) {
				int side = rand() % 2;
				int pelletNum = 5;
				float spread = 1.0f;
				int enemyBullets = 0;
				for (int x = 133; x < 533; x++)  // Used to count how many bullets are flying
				{
					if (objectArray[x]) enemyBullets++;
				}
				if (enemyBullets < 400) {
					for (int i = 0; i < pelletNum; i++) {
						int index = 133;
						while (objectArray[index]) {
							index++;
						}
						if (side == 1) {
							double theta = e.getTheta((float(e.GetX()) + spread), (float(e.GetY()) + 20.0f), objectArray[132]->getCenterX(), objectArray[132]->getCenterY());
							if (theta > 0) {
								Object_Bullets_Enemy* eb = new Object_Bullets_Enemy(index, e.angMoveX(theta + ((((spread * (rand() % 16)) * (rand() % 3) - 1)) * e.PI / 180), speed), e.angMoveY(theta + ((((spread * (rand() % 16)) * (rand() % 3) - 1)) * e.PI / 180), speed + (0.3f * (rand() % 3 - 1))), int(e.GetX() + 5), int(e.GetY() + 20), imgERiceRed, imgExplode, objectArray, 1.0f);
								objectArray[index] = eb;  // puts the bullet in the open spot in the array.
							}
							else {
								Object_Bullets_Enemy* eb = new Object_Bullets_Enemy(index, e.angMoveX(theta + ((((spread * (rand() % 16)) * (rand() % 3) - 1)) * e.PI / 180), speed), -e.angMoveY(theta + ((((spread * (rand() % 16)) * (rand() % 3) - 1)) * e.PI / 180), -speed + (0.3f * (rand() % 3 - 1))), int(e.GetX() + 5), int(e.GetY() + 20), imgERiceRed, imgExplode, objectArray, 1.0f);
								objectArray[index] = eb;  // puts the bullet in the open spot in the array.
							}
						}
						else {
							double theta = e.getTheta((float(e.GetX()) + spread), (float(e.GetY()) + 20.0f), objectArray[132]->getCenterX(), objectArray[132]->getCenterY());
							if (theta > 0) {
								Object_Bullets_Enemy* eb = new Object_Bullets_Enemy(index, e.angMoveX(theta + ((((spread * (rand() % 16)) * (rand() % 3) - 1)) * e.PI / 180), speed), e.angMoveY(theta + ((((spread * (rand() % 16)) * (rand() % 3) - 1)) * e.PI / 180), speed + (0.3f * (rand() % 3 - 1))), int(e.GetX() + 35), int(e.GetY() + 20), imgERiceRed, imgExplode, objectArray, 1.0f);
								objectArray[index] = eb;  // puts the bullet in the open spot in the array.
							}
							else {
								Object_Bullets_Enemy* eb = new Object_Bullets_Enemy(index, e.angMoveX(theta + ((((spread * (rand() % 16)) * (rand() % 3) - 1)) * e.PI / 180), speed), -e.angMoveY(theta + ((((spread * (rand() % 16)) * (rand() % 3) - 1)) * e.PI / 180), -speed + (0.3f * (rand() % 3 - 1))), int(e.GetX() + 35), int(e.GetY() + 20), imgERiceRed, imgExplode, objectArray, 1.0f);
								objectArray[index] = eb;  // puts the bullet in the open spot in the array.
							}
						}
					}
				}
			}
		}
	};

	auto Shot_Delay_PartingArc = [&](Object_Enemy& e, float speed, long delay) {
		if (e.getTime() < 60) {
			Shot_None(e, speed);
		}
		else if (e.getTime() < 60 + delay) {
			if (e.getTime() % 30 == 0) {
				int side = rand() % 2;
				int pelletNum = 5;
				int enemyBullets = 0;
				for (int x = 133; x < 533; x++)  // Used to count how many bullets are flying
				{
					if (objectArray[x]) enemyBullets++;
				}
				if (enemyBullets < 400) {
					for (int i = 0; i < pelletNum; i++) {
						int index = 133;
						while (objectArray[index]) {
							index++;
						}
						if (side == 1) {
							double theta = e.getTheta((float(e.GetX())), (float(e.GetY()) + 20.0f), objectArray[132]->getCenterX(), objectArray[132]->getCenterY()) + (2 * (i - 3) * e.PI / 180.0f);
							if (theta > 0) {
								Object_Bullets_Enemy* eb = new Object_Bullets_Enemy(index, e.angMoveX(theta, speed), e.angMoveY(theta, speed), int(e.GetX() + 5), int(e.GetY() + 20), imgEFleaGreen, imgExplode, objectArray, 1.0f);
								objectArray[index] = eb;  // puts the bullet in the open spot in the array.
							}
							else {
								Object_Bullets_Enemy* eb = new Object_Bullets_Enemy(index, e.angMoveX(theta, speed), -e.angMoveY(theta, -speed), int(e.GetX() + 5), int(e.GetY() + 20), imgEFleaGreen, imgExplode, objectArray, 1.0f);
								objectArray[index] = eb;  // puts the bullet in the open spot in the array.
							}
						}
						else {
							double theta = e.getTheta((float(e.GetX())), (float(e.GetY()) + 20.0f), objectArray[132]->getCenterX(), objectArray[132]->getCenterY()) + (2 * (i - 3) * e.PI / 180.0f);
							if (theta > 0) {
								Object_Bullets_Enemy* eb = new Object_Bullets_Enemy(index, e.angMoveX(theta, speed), e.angMoveY(theta, speed), int(e.GetX() + 35), int(e.GetY() + 20), imgEFleaGreen, imgExplode, objectArray, 1.0f);
								objectArray[index] = eb;  // puts the bullet in the open spot in the array.
							}
							else {
								Object_Bullets_Enemy* eb = new Object_Bullets_Enemy(index, e.angMoveX(theta, speed), -e.angMoveY(theta, -speed), int(e.GetX() + 35), int(e.GetY() + 20), imgEFleaGreen, imgExplode, objectArray, 1.0f);
								objectArray[index] = eb;  // puts the bullet in the open spot in the array.
							}
						}
					}
				}
			}
		}
	};

	//initialize global variables
	objectCount = pBullets + eShips + pBomb + pShips + pHitbox + eBullets;

	objectArray = new Object_Game * [objectCount];
	for (int goCurrent = 0; goCurrent < objectCount; goCurrent++) {
		objectArray[goCurrent] = NULL;
	}

	spawns = {
		new Object_Enemy(0, 0, 0, 10, 0, 1.5F, 1.0F, 300, imgEFighterCyan, imgExplode, objectArray, 120, Move_Delay_Straight, Shot_Delay_Aimed, 25, 100, 1.0f),
		new Object_Enemy(0, 0, 0, 310, 0, 1.5F, 1.0F, 300, imgEFighterCyan, imgExplode, objectArray, 120, Move_Delay_Straight, Shot_Delay_Aimed, 25, 100, 1.0f),
		new Object_Enemy(0, 0, 0, 70, 0, 1.5F, 1.0F, 300, imgEFighterCyan, imgExplode, objectArray, 240, Move_Delay_Straight, Shot_Delay_Aimed, 25, 100, 1.0f),
		new Object_Enemy(0, 0, 0, 260, 0, 1.5F, 1.0F, 300, imgEFighterCyan, imgExplode, objectArray, 240, Move_Delay_Straight, Shot_Delay_Aimed, 25, 100, 1.0f),

		new Object_Enemy(0, 0, 0, 10, 0, 1.0F, 1.0F, imgEFighterCyan, imgExplode, objectArray, 600, Move_Curve_Right, Shot_Straight, 25, 100, 1.0f),
		new Object_Enemy(0, 0, 0, 70, 0, 1.0F, 1.0F, imgEFighterCyan, imgExplode, objectArray, 600, Move_Curve_Right, Shot_Straight, 25, 100, 1.0f),
		new Object_Enemy(0, 0, 0, 130, 0, 1.0F, 1.0F, imgEFighterCyan, imgExplode, objectArray, 600, Move_Curve_Right, Shot_Straight, 25, 100, 1.0f),
		new Object_Enemy(0, 0, 0, 190, 0, 1.0F, 1.0F, imgEFighterCyan, imgExplode, objectArray, 600, Move_Curve_Right, Shot_Straight, 25, 100, 1.0f),

		new Object_Enemy(0, 0, 0, (SCREENWIDTH / 5) - 25, 0, 1.0F, 1.0F, imgEFighterPurple, imgExplode, objectArray, 900, Move_Sinusoid, Shot_Scatter, 25, 100, 1.0f),
		new Object_Enemy(0, 0, 0, (3.0f * SCREENWIDTH / 5) - 25, 0, 1.0F, 1.0F,imgEFighterPurple, imgExplode, objectArray, 900, Move_Sinusoid, Shot_Scatter, 25, 100, 1.0f),

		new Object_Enemy(0, 0, 0, 10, 0, 1.5F, 0.5F, 400, imgEFighterBlue, imgExplode, objectArray, 1300, Move_Delay_Straight, Shot_Delay_Circle, 25, 100, 1.0f),
		new Object_Enemy(0, 0, 0, 310, 0, 1.5F, 0.5F, 400, imgEFighterBlue, imgExplode, objectArray, 1300, Move_Delay_Straight, Shot_Delay_Circle, 25, 100, 1.0f),

		new Object_Enemy(0, 0, 0, 10, 0, 1.5F, 1.0f, 400, imgEFighterGreen, imgExplode, objectArray, 1600, Move_Delay_Curve_Right, Shot_Delay_Arc, 25, 100, 1.0f),
		new Object_Enemy(0, 0, 0, 70, 0, 1.5F, 1.0f, 400, imgEFighterGreen, imgExplode, objectArray, 1600, Move_Delay_Curve_Right, Shot_Delay_Arc, 25, 100, 1.0f),

		new Object_Enemy(0, 0, 0, 260, 0, 1.5F, 1.0f, 400, imgEFighterRed, imgExplode, objectArray, 1900, Move_Delay_Curve_Left, Shot_Delay_Grape, 25, 100, 1.0f),
		new Object_Enemy(0, 0, 0, 310, 0, 1.5F, 1.0f, 400, imgEFighterRed, imgExplode, objectArray, 1900, Move_Delay_Curve_Left, Shot_Delay_Grape, 25, 100, 1.0f),

		new Object_Enemy(0, 0, 0, 160, 0, 0.5F, 1.0f, imgEFighterPink, imgExplode, objectArray, 2500, Move_Kamikaze, Shot_Spiral, 100, 500, 1.0f),
	};

	Object_Player* p1 = new Object_Player(131, 0.0f, 0.0f, SCREENWIDTH / 2, SCREENHEIGHT - 60, imgShip, objectArray);
	objectArray[131] = p1;
	Object_Player* p2 = new Object_Player(132, 0.0f, 0.0f, p1->getCenterX() - 3, p1->getCenterY() - 2, imgHitbox, objectArray);
	objectArray[132] = p2;

	//fire control vars
	pBulletCount = 0;
	nextFireX = 0;
	nextFireY = 0;
	shotNumber = 1;
	shooting = false;
	pBombCount = 3;
	hasBombed = false;

	//level global vars
	points = 0;
	pLifeCount = 3;
	isDead = false;
	ticksDead = 0;
	isGameOver = false;
	hasCleaned = false;

	//level music
	mciSendString("play LevelLoop.mp3 repeat", NULL, 0, NULL);
}

void Level_Main::Render() {
	if (!isGameOver) {
		//gfx->ClearScreen(0.0f, 0.0f, 0.0f);
		for (int goCurrent = 0; goCurrent < objectCount; goCurrent++) {
			if (objectArray[goCurrent]) objectArray[goCurrent]->Render();
		}
		infoBox->Draw(0, SCREENWIDTH + 2, 1.0f);
		txtScore->RenderText();
		txtLives->RenderText();
		for (int i = pLifeCount; i > 0; i--) {
			iconLife->Draw(SCREENWIDTH + 225 - (i * 40), 300);
		}
		txtBombs->RenderText();
		for (int i = pBombCount; i > 0; i--) {
			iconBomb->Draw(SCREENWIDTH + 225 - (i * 40), 350);
		}
	}
	else {
		if (spawns.empty()) {
			txtVictory->RenderText();
		}
		else {
			txtDefeat->RenderText();
		}
		clock_t sinceLoadTime = (clock() - ticks * 60) / CLOCKS_PER_SEC;
		if (sinceLoadTime % 2 == 0) {
			txtGameMsg->RenderText();
		}
		infoBox->Draw(0, SCREENWIDTH + 2, 1.0f);
		txtScore->RenderText();
	}
	delete txtPoints;
	txtPoints = new Object_Text(gfx, D2D1::RectF(SCREENWIDTH + 35, 150, SCREENWIDTH + 225, SCREENHEIGHT - 250), points, L"Consolas", 15.0f, D2D1::ColorF::White, 1.0f, TRUE, TRUE);
	txtPoints->RenderText();
}

void Level_Main::UnLoad() {
}

void Level_Main::EndState() {
	mciSendString("stop LevelLoop.mp3", NULL, 0, NULL);
	//delete game objects;
	for (int curObj = 0; curObj < objectCount; curObj++) {
		if (objectArray[curObj]) delete objectArray[curObj];
	}
	delete[] objectArray;

	//delete sprites
	if (imgShip) delete imgShip;
	if (imgHitbox) delete imgHitbox;
	if (imgPlayerBullet) delete imgPlayerBullet;
	if (imgPlayerLaser) delete imgPlayerLaser;
	if (imgBomb) delete imgBomb;
	if (imgExplode) delete imgExplode;
	if (imgEFighterRed) delete imgEFighterRed;
	if (imgEFighterYellow) delete imgEFighterYellow;
	if (imgEFighterGreen) delete imgEFighterGreen;
	if (imgEFighterCyan) delete imgEFighterCyan;
	if (imgEFighterBlue) delete imgEFighterBlue;
	if (imgEFighterPurple) delete imgEFighterPurple;
	if (imgEFighterPink) delete imgEFighterPink;
	if (imgEFleaCyan) delete imgEFleaCyan;
	if (imgERiceRed) delete imgERiceRed;
	if (imgEFleaGreen) delete imgEFleaGreen;
	if (imgEBallBlue) delete imgEBallBlue;
	if (imgERicePurple) delete imgERicePurple;
	if (imgEFleaPink) delete imgEFleaPink;
	if (imgEBomb) delete imgEBomb;
	if (imgEBomber) delete imgEBomber;
	if (iconBomb) delete iconBomb;
	if (iconLife) delete iconLife;
}

void Level_Main::Update() {
	if (isGameOver) {
		if (!hasCleaned) {
			Level_Main::EndState();
			hasCleaned = true;
		}
		if (GetKeyState('Z') & 0x8000) {
			GameController::SwitchLevel(new Level_Main());
		}
		return;
	}

	ticks++;

	Object_Explosion* tempDead = dynamic_cast<Object_Explosion*>(objectArray[131]);
	//if the player died, start a countdown so we can respawn after that
	if (tempDead) {
		isDead = true;
		if (pLifeCount == 0) {
			isGameOver = TRUE;
		}
		for (int idx = 133; idx < 533; idx++) {
			if (objectArray[idx]) {
				delete objectArray[idx];
				objectArray[idx] = NULL;
			}
		}
	}

	if (isDead) {
		if (ticksDead > 60 && pLifeCount > 0) {
			isDead = false;
			pLifeCount--;
			pBombCount = 3;
			Object_Player* p1 = new Object_Player(131, 0.0f, 0.0f, SCREENWIDTH / 2, SCREENHEIGHT - 60, imgShip, objectArray);
			objectArray[131] = p1;
			ticksDead = 0;
		}
	}

	//if the player has bombed, reduce bomb count here (input overflow prevention of reducing bombs to zero by pressing X once)
	if (hasBombed) {
		hasBombed = false;
		pBombCount--;
	}

	//load any new enemies
	bool newEm = true;
	while (newEm) {
		if (spawns.empty()) {
			isGameOver = true;
			for (int x = 100; x < 129; x++)  // Used to count how many enemies are flying
			{
				if (objectArray[x]) {
					isGameOver = false;
				}
			}
			newEm = false;
		}
		else if (spawns.front()->getSpawn() == ticks) {
			int numEnemies = 0;
			for (int x = 100; x < 129; x++)  // Used to count how many enemies are flying
			{
				if (objectArray[x]) numEnemies++;
			}
			if (numEnemies < 30) {
				int index = 100;
				while (objectArray[index]) {
					index++;
				}
				Object_Enemy* temp = spawns.front();
				temp->setIndex(index);
				objectArray[index] = temp;
				spawns.pop_front();
			}
		}
		else {
			newEm = false;
		}
	}

	//kill any dead enemies
	for (int goCurrent = 100; goCurrent < 129; goCurrent++) {
		Object_Enemy* temp = dynamic_cast<Object_Enemy*>(objectArray[goCurrent]);
		if (temp) {
			if (temp->getHealth() <= 0) {
				points += temp->getPoints();
				Object_Explosion* boom = new Object_Explosion(goCurrent, objectArray[goCurrent]->GetX(), this->objectArray[goCurrent]->GetY(), imgExplode, objectArray, 30, 5);
				this->objectArray[goCurrent] = boom;  // This will use the enemy position for the explosion
				mciSendString("play Explode.mp3", NULL, 0, NULL);
				return;
			}
		}
	}

	//all sprites update behavior
	for (int goCurrent = 0; goCurrent < objectCount; goCurrent++) {
		if (objectArray[goCurrent]) objectArray[goCurrent]->Update();
	}

	if (!isDead) {
		Object_Player* p1 = (Object_Player*)objectArray[131];

		//Remember: 0,0 is the upper left corner.
		//Subtracting from x will move left, Subtracting from y will move up.
		int shipVelocity = 7;

		//Arrowkeys to move the player ship
		if (GetKeyState(VK_LSHIFT) & 0x8000) {
			shipVelocity = 3;
		}
		if (!GetKeyState(VK_LSHIFT) & 0x8000) {
			shipVelocity = 7;
		}

		//Eight Directional Movement
		if ((GetKeyState(VK_LEFT) & 0x8000) && (GetKeyState(VK_UP) & 0x8000)) {
			p1->Setvelocity(-shipVelocity / sqrt(2.0f), -shipVelocity / sqrt(2.0f));
		}
		else if ((GetKeyState(VK_LEFT) & 0x8000) && (GetKeyState(VK_DOWN) & 0x8000)) {
			p1->Setvelocity(-shipVelocity / sqrt(2.0f), shipVelocity / sqrt(2.0f));
		}
		else if ((GetKeyState(VK_RIGHT) & 0x8000) && (GetKeyState(VK_UP) & 0x8000)) {
			p1->Setvelocity(shipVelocity / sqrt(2.0f), -shipVelocity / sqrt(2.0f));
		}
		else if ((GetKeyState(VK_RIGHT) & 0x8000) && (GetKeyState(VK_DOWN) & 0x8000)) {
			p1->Setvelocity(shipVelocity / sqrt(2.0f), shipVelocity / sqrt(2.0f));
		}
		else if (GetKeyState(VK_RIGHT) & 0x8000) {
			p1->Setvelocity(shipVelocity, 0);
		}
		else if (GetKeyState(VK_UP) & 0x8000) {
			p1->Setvelocity(0, -shipVelocity);
		}
		else if (GetKeyState(VK_DOWN) & 0x8000) {
			p1->Setvelocity(0, shipVelocity);
		}
		else if (GetKeyState(VK_LEFT) & 0x8000) {
			p1->Setvelocity(-shipVelocity, 0);
		}

		//bomb clears all enemy bullets and small enemies
		if (GetKeyState('X') & 0x8000) {
			if (pBombCount > 0) {
				if (!objectArray[130]) {
					Object_Bomb_Player* b1 = new Object_Bomb_Player(130, objectArray[131]->getCenterX() - 370, objectArray[131]->getCenterY() - 573, imgBomb, objectArray, 16, 3, 1.0f);
					objectArray[130] = b1;
					hasBombed = true;
					mciSendString("play bomb2.mp3", NULL, 0, NULL);
				}
			}
		}

		//alternate the shot location like a friggin Supermarine Spitfire
		if (shotNumber == 3) {
			if (shooting) {
				nextFireX = nextFireX + 12;
			}
			if (nextFireX > 50) {
				nextFireX = 0;
			}
			if (nextFireX == 0 || nextFireX == 48) {
				nextFireY = 40;
			}
			if (nextFireX == 12 || nextFireX == 36) {
				nextFireY = 20;
			}
			if (nextFireX == 20) {
				nextFireY = 0;
			}
		}
		//focused movement and increased attack with main laser
		if ((GetKeyState('Z') & 0x8000) && (GetKeyState(VK_LSHIFT) & 0x8000)) {
			int numPlayerBullets = 0;
			for (int x = 0; x < 99; x++)  // Used to count how many bullets are flying
			{
				if (objectArray[x]) numPlayerBullets++;
			}
			if (numPlayerBullets < 100) {
				int index = 0;
				while (objectArray[index]) {
					index++;
				}
				Object_Bullets_PlayerLaser* pb = new Object_Bullets_PlayerLaser(index, 100, 130, 0.0f, -10.0f, int((objectArray[131]->GetX() - 5)), objectArray[131]->GetY(), imgPlayerLaser, objectArray);  // Creates a bullet and gives it an x & y position based on where the player ship is.
				objectArray[index] = pb;  // puts the bullet in the open spot in the array.
			}
			shooting = true;
		}

		//Z to fire
		else if (GetKeyState('Z') & 0x8000) {
			if (shotNumber % 3 == 0) {
				int numPlayerBullets = 0;
				for (int x = 0; x < 99; x++)  // Used to count how many bullets are flying
				{
					if (objectArray[x]) numPlayerBullets++;
				}

				if (numPlayerBullets < 100) {
					int index = 0;
					while (objectArray[index]) {
						index++;  // This loop finds the first open bullet position.
					}
					Object_Bullets_Player* pb = new Object_Bullets_Player(index, 100, 130, 0.0f, -10.0f, int((objectArray[131]->GetX() + nextFireX - 5)), objectArray[131]->GetY() + nextFireY, imgPlayerBullet, objectArray);  // Creates a bullet and gives it an x & y position based on where the player ship is.

					objectArray[index] = pb;  // puts the bullet in the open spot in the array.
					mciSendString("play laser.mp3", NULL, 0, NULL);
				}
				shotNumber = 1;
			}
			else {
				shotNumber++;
			}
			shooting = true;
		}
		else if (!(GetKeyState('Z') & 0x8000)) {
			shooting = false;
		}

		//move hitbox to match player
		Object_Player* p2 = new Object_Player(132, 0.0f, 0.0f, p1->getCenterX() - 3, p1->getCenterY() - 2, imgHitbox, objectArray);
		objectArray[132] = p2;
	}
	else {
		ticksDead++;
		//move hitbox to flipping nowhere to prevent collisions for a bit
		Object_Player* p2 = new Object_Player(132, 0.0f, 0.0f, SCREENWIDTH / 2, SCREENHEIGHT + 10, imgHitbox, objectArray);
		objectArray[132] = p2;
	}

	//Escape key ends program
	if (GetKeyState(VK_ESCAPE) & 0x8000)
		GameController::QuitGame();
}

long Level_Main::getTicks() {
	return ticks;
}