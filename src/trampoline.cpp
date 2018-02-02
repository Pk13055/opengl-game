/*

	trampoline function definitions

*/

#include <utility>
#include <cmath>
#include "main.h"
#define RECTANGLE 1
#include "trampoline.h"

Trampoline::Trampoline(float x, float y, color_t color) {
	this->set_position(x, y);
	this->length = 1.6f;
	this->width = 1.5f;
	this->rotation = 0.0f;
	this->color = color;
	GLfloat vertex_buffer_data[] ={
        0.9f, 0.0f, 0.0f,
        0.9f, 1.5f, 0.0f,
        0.7f, 1.0f, 0.0f,

        0.9f, 0.0f, 0.0f,
        0.7f, 1.5f, 0.0f,
        0.7f, 0.0f, 0.0f,

        0.7f, 1.0f, 0.0f,
       -0.7f, 1.0f, 0.0f,
        0.0f, 0.0f, 0.0f,

       -0.7f, 0.0f, 0.0f,
       -0.9f, 1.5f, 0.0f,
       -0.7f, 1.0f, 0.0f,

       -0.7f, 0.0f, 0.0f,
       -0.9f, 1.5f, 0.0f,
       -0.9f, 0.0f, 0.0f
    };
    this->object = create3DObject(GL_TRIANGLES, 5 * 3, vertex_buffer_data, color, GL_FILL);
}

void Trampoline::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 0, 1));
    rotate          = rotate * glm::translate(glm::vec3(0, 0, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}

void Trampoline::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

bounding_box_t Trampoline::bounding_box() {
    float x = this->position.x, y = this->position.y;
    bounding_box_t bbox = { x, y };
    bbox.role = RECTANGLE;
    bbox.rotation = this->rotation;
    bbox.size = make_pair(this->length, this->width);
    return bbox;
}

