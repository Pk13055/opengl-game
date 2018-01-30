#include "main.h"

#ifndef CIRCLE_H
#define CIRCLE_H


class Circle {
public:
    Circle() {}
    Circle(float x, float y, color_t color,  float radius = 0.3f);
    glm::vec3 position;
    float rotation;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    virtual void tick() = 0;
    double xspeed;
    double yspeed;
    double radius;
    bounding_box_t bounding_box();
private:
    VAO *object;
};

#endif // CIRCLE_H
