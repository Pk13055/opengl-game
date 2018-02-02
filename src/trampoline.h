#include "main.h"
#ifndef TRAMPOLINE_H
#define TRAMPOLINE_H


class Trampoline {
public:
	Trampoline(float x, float y, color_t color);
	glm::vec3 position;
	color_t color;
    float rotation = 0.0f;
    void draw(glm::mat4 VP);
    double length, width;
    void set_position(float x, float y);
    bounding_box_t bounding_box();
private:
    VAO *object;
};

#endif // TRAMPOLINE_H
