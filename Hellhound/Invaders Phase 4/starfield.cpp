#include "starfield.h"

//size of the different star sizes in pixels
float smallSize = 0.0f;
float mediumSize = 0.1f;
float largeSize = 0.2f;

starfield::starfield() : maxSmallStars(0), maxMediumStars(0), maxLargeStars(0), x_Size(800), y_Size(600)
{
}

starfield::starfield(int xResolution, int yResolution, Graphics* gfx)
{
	x_Size = xResolution;
	y_Size = yResolution;
	this->gfx = gfx;

	//init random generator
	my_distribution_x = std::uniform_int_distribution<int>(0, xResolution);
	my_distribution_y = std::uniform_int_distribution<int>(0, yResolution);
	re_x.seed(std::time(0));
	re_y.seed(std::time(0) + 24);

	//The higher reduceStars the fewer stars; classDifference sets the proportionality between small, medium and large stars. The higher the number, the fewer stars in each larger class.
	int reduceStars = 18;
	int classDifference = 3;

	maxSmallStars = (xResolution / (reduceStars * 10)) * (yResolution / reduceStars);
	maxMediumStars = (xResolution / (reduceStars * 10 * classDifference)) * (yResolution / (reduceStars * classDifference));
	maxLargeStars = (xResolution / (reduceStars * 10 * classDifference * classDifference)) * (yResolution / (reduceStars * classDifference * classDifference));

	//generate a start set of stars
	while ((int)smallStars.size() <= maxSmallStars) {
		smallStars.push_back(star(my_distribution_x(re_x), my_distribution_y(re_y), smallSize, gfx));
	}

	while ((int)mediumStars.size() <= maxMediumStars) {
		mediumStars.push_back(star(my_distribution_x(re_x), my_distribution_y(re_y), mediumSize, gfx));
	}

	while ((int)largeStars.size() <= maxLargeStars) {
		largeStars.push_back(star(my_distribution_x(re_x), my_distribution_y(re_y), largeSize, gfx));
	}
}

void starfield::updateStarfield()
{
	//remove all stars that have exceeded the lower screen border
	smallStars.erase(remove_if(smallStars.begin(), smallStars.end(), [&](star& p_Star) {
		return (p_Star.getYPos() > y_Size);
		}
	), smallStars.end());

	mediumStars.erase(remove_if(mediumStars.begin(), mediumStars.end(), [&](star& p_Star) {
		return (p_Star.getYPos() > y_Size);
		}
	), mediumStars.end());

	largeStars.erase(remove_if(largeStars.begin(), largeStars.end(), [&](star& p_Star) {
		return (p_Star.getYPos() > y_Size);
		}
	), largeStars.end());

	//move every star, according to its size to create a parallax effect
	for_each(smallStars.begin(), smallStars.end(), [&](star& p_Star) {
		p_Star.addYPos(1);
		}
	);

	for_each(mediumStars.begin(), mediumStars.end(), [&](star& p_Star) {
		p_Star.addYPos(2);
		}
	);

	for_each(largeStars.begin(), largeStars.end(), [&](star& p_Star) {
		p_Star.addYPos(1);
		}
	);

	//create new stars until the set limit is reached
	while ((int)smallStars.size() <= maxSmallStars) {
		smallStars.push_back(star(my_distribution_x(re_x), 0, smallSize, gfx));
	}

	while ((int)mediumStars.size() <= maxMediumStars) {
		mediumStars.push_back(star(my_distribution_x(re_x), 0, mediumSize, gfx));
	}

	while ((int)largeStars.size() <= maxLargeStars) {
		largeStars.push_back(star(my_distribution_x(re_x), 0, largeSize, gfx));
	}
}

//update a target texture with all stars contained in this starfield
void starfield::render()
{
	gfx->ClearScreen(0.0f, 0.0f, 0.0f);

	for (vector<star>::iterator it = smallStars.begin(); it != smallStars.end(); ++it) {
		it->star::render();
	}

	for (vector<star>::iterator it = mediumStars.begin(); it != mediumStars.end(); ++it) {
		it->star::render();
	}

	for (vector<star>::iterator it = largeStars.begin(); it != largeStars.end(); ++it) {
		it->star::render();
	}
}