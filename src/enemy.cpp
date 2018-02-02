/*
	modify all enemy code here

*/

#include "main.h"
#include "enemy.h"
#include <iostream>

#define RATE_Y 0.01
#define RATE_X 0.001

using namespace std;

int Enemy::enemy_count = 0;

// constructors
Enemy::Enemy(float x, float y, color_t color, float radius = 0.4f)
: Circle(-5.0f + rand() % 11,
		0.3f + radius + rand() % 30,
		color,
		0.3f + 0.06f * (float) (rand() % 5)) {
	Enemy::enemy_count++;
	this->id = Enemy::enemy_count;
	this->xspeed = 0.02f + 0.03f * (float) (rand() % 3);
}

void Enemy::tick() {
	this->position.x += this->xspeed;
	if(this->position.x > 5.0f + this->radius)
		this->position.x = -5.0f - this->radius;
}


