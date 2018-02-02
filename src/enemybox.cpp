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
	this->parent = &parent;
	this->xspeed = this->parent->xspeed;
	this->yspeed = this->parent->yspeed;
	this->id = this->parent->id;
	this->reference = parent.position;

	EnemyBox::box_count++;
	this->rotation =  -10.0f * (double) (rand() % 18 + rand() % 2);
	this->set_position(this->parent->position.x + (this->parent->radius + this->width / 2.0f)
		* cos(-this->rotation * M_PI / 180.0f),
		this->parent->position.y + (this->parent->radius + this->width / 2.0f)
		* sin(-this->rotation * M_PI / 180.0f));

}

// tick the enemy box similar to the enemy
void EnemyBox::tick() {
	this->position.x += this->xspeed;
	if(this->position.x > 5.0f + this->width)
		this->set_position(this->parent->position.x + (this->parent->radius + this->width / 2.0f)
		* cos(-this->rotation * M_PI / 180.0f),
		this->parent->position.y + (this->parent->radius + this->width / 2.0f)
		* sin(-this->rotation * M_PI / 180.0f));
}
