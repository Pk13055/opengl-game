#include "main.h"
#include "circle.h"
#ifndef ENEMY_H
#define ENEMY_H


class Enemy: public Circle {
public:
    Enemy(float x, float y, color_t color, float radius);
    int id;
    virtual void tick();
    static int enemy_count;
private:
    VAO *object;
};

#endif // ENEMY_H
