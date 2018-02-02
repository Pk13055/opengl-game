/*
	player overriden functionality
*/

#include "main.h"
#include "player.h"
#include <iostream>

using namespace std;

#define RATE_Y 0.008f
#define RATE_X 0.001f
#define POND_WIDTH 3.5f
#define WATER_RATE_Y 0.001f
#define WATER_RATE_X 0.03f

void Player::tick() {

	this->position.x -= xspeed;
    this->position.y += yspeed;

    if(this->position.y < -2.5f || this->position.y > 2.5f)
    	screen_center_y = this->position.y;

    // if(fabs(this->position.x - screen_center_x) < 1.25f || fabs(this->position.x - screen_center_x) > 3.0f)
    // 	screen_center_x = this->position.x;

	if(this->position.y > 0) yspeed -= RATE_Y;
	else if(this->position.x > - POND_WIDTH / 2 && this->position.x < POND_WIDTH / 2) {
		if(this->position.y > -0.3f) yspeed = -WATER_RATE_Y;
		if(this->position.y < -2.5f + 2 * this->radius)
			this->position.y = -2.5f + 2 * this->radius,
			this->yspeed = 0, this->xspeed = 0;
		this->yspeed -= WATER_RATE_Y;
	}
	else yspeed = 0.0f, this->position.y = 0;

	if(this->position.x > 5.0f + this->radius)
		this->position.x = -5.0f - this->radius;
	else if(this->position.x < -5.0f - this->radius)
		this->position.x = 5.0f - this->radius;

}
