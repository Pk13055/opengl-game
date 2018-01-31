/*
	declare all enemy box functions here

*/

#include "main.h"
#include "enemy.h"
#include <vector>
#include <utility>
#include <cmath>
using namespace std;

#define RATE_X 0.01
#define RATE_Y 0.01
#include "enemybox.h"

int EnemyBox::box_count = 0;

EnemyBox::EnemyBox(Enemy &parent, color_t color)
: Rect(0.0f, 0.0f,
 0.8f + 0.1f * (rand() % 4),
 0.06f + 0.1f * (rand() % 3), color) {

	// inherit the speeds
	this->xspeed = parent.xspeed;
	this->yspeed = parent.yspeed;
	this->id = parent.id;
	this->parent = &parent;
	this->reference = parent.position;

	EnemyBox::box_count++;
	this->rotation =  -10.0f * (double) (rand() % 18);
	this->set_position(parent.position.x + (parent.radius + this->width / 2.0f)
		* cos(-this->rotation * M_PI / 180.0f),
		parent.position.y + (parent.radius + this->width / 2.0f)
		* sin(-this->rotation * M_PI / 180.0f));

}

// tick the enemy box similar to the enemy
void EnemyBox::tick() {
	this->position.x += this->xspeed;
	if(this->position.x > 5.0f + this->width)
		this->position.x = -5.0f + this->width / 2.0f;
}
