/*
	definition of static porcupine
*/

#include "main.h"
#include "rect.h"
#ifndef PORCUPINE_H
#define PORCUPINE_H


class Porcupine {
public:
    Porcupine(float x, float y, float length, float width, color_t color);
    glm::vec3 position, original;
    float rotation;
    bool visible = true;
    double length, width,
    yspeed, xspeed;
    color_t color;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void tick();
    bounding_box_t bounding_box();
private:
    VAO *object;
};

#endif // PORCUPINE_H
