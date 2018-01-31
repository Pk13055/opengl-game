/*
	definition of enemy boxes for the circle enemies
*/

#include "main.h"
#include "rect.h"
#include "enemy.h"

#ifndef ENEMYBOX_H
#define ENEMYBOX_H

class EnemyBox : public Rect {
public:
	EnemyBox(Enemy &parent, color_t color);
	double xspeed, yspeed;
	int id;
	glm::vec3 reference;
	void tick();
	static int box_count;

private:
	VAO *object;
	Enemy *parent;
};


#endif // ENEMYBOX_H
