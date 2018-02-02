/*
	definition of static rectangles
*/

#include "main.h"
#ifndef RECT_H
#define RECT_H


class Rect {
public:
    Rect(float x, float y, float length, float width, color_t color);
    glm::vec3 position;
    float rotation;
    double length, width;
    color_t color;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    virtual void tick();
    bounding_box_t bounding_box();
private:
    VAO *object;
};

#endif // RECT_H
