/*
	player overriden functionality
*/

#include "main.h"
#include "player.h"
#include <iostream>

using namespace std;

#define RATE_Y 0.008
#define RATE_X 0.001

void Player::tick() {
	this->position.x -= xspeed;
    this->position.y += yspeed;

	if(this->position.y > 0) yspeed -= RATE_Y;
	else yspeed = 0, this->position.y = 0;

	if(this->position.x > 5.0f + this->radius)
		this->position.x = -5.0f - this->radius;
	else if(this->position.x < -5.0f - this->radius)
		this->position.x = 5.0f - this->radius;
}
