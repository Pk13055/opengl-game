#include "main.h"
#include "circle.h"
#define offset 0.5f
#ifndef PLAYER_H
#define PLAYER_H


class Player: public Circle {
public:
	Player() : Circle() {}
	Player(float x, float y, color_t color, float radius = 0.4f) :
	Circle(x, y, color, radius) {}
	int lives = 100;
	virtual void tick();
private:
    VAO *object;
};

#endif // PLAYER_H
