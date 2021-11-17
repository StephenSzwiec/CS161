#pragma once
#include "star.h"
#include <random>
#include <vector>
#include <ctime>

using std::vector;

class starfield
{
public:
	starfield();
	starfield(int, int, Graphics*);
	~starfield() {}

	void updateStarfield();
	void render();

protected:
	Graphics* gfx;

	int maxSmallStars;
	int maxMediumStars;
	int maxLargeStars;

	int x_Size;
	int y_Size;

	vector<star> smallStars;
	vector<star> mediumStars;
	vector<star> largeStars;

	std::default_random_engine re_x;
	std::default_random_engine re_y;
	std::uniform_int_distribution<int> my_distribution_x;
	std::uniform_int_distribution<int> my_distribution_y;
};
