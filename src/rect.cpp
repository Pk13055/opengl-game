/*
	common function definitions

*/

#include "main.h"
#include <math.h>
#include <vector>
#include <utility>
using namespace std;

#define RATE_X 0.01
#define RATE_Y 0.01
#include "rect.h"


Rect::Rect(float x, float y, float length, float width, color_t color) {
	this->set_position(x, y);
	this->length = length;
	this->width = width;
	this->color = color;
	int total_shapes = 2, i = 0;
	GLfloat vertex_buffer_data[(int) total_shapes * 3 * 3] = {};

	for(double x_coord = this->position.x - this->length / 2.0f;
	 x_coord <= this->position.x + this->length / 2.0f;
	  x_coord += this->length)
		for(double y_coord = this->position.y - this->width / 2.0f;
	 y_coord <= this->position.y + this->width / 2.0f;
	  y_coord += this->width) {
			vertex_buffer_data[i++] = x_coord;
			vertex_buffer_data[i++] = y_coord;
			vertex_buffer_data[i++] = 0.0f;
		}

	for(int pos = 1; pos <= 2; pos++) {
		int fac = (pos % 2) * -2 + 1;
		vertex_buffer_data[i++] = this->position.x + fac * this->length / 2.0f;
		vertex_buffer_data[i++] = this->position.y - fac * this->width / 2.0f;
		vertex_buffer_data[i++] = 0.0f;
	}
	this->object = create3DObject(GL_TRIANGLES, total_shapes * 3, vertex_buffer_data, color, GL_FILL);
}

void Rect::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 0, 1));
    rotate          = rotate * glm::translate(glm::vec3(0, 0, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}

void Rect::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

bounding_box_t Rect::bounding_box() {
    float x = this->position.x, y = this->position.y;
    bounding_box_t bbox = { x, y };
    bbox.role = RECTANGLE;
    bbox.rotation = this->rotation;
    bbox.size = make_pair(this->length, this->width);
    return bbox;
}

// have to define for non pure virtual function
void Rect::tick() {}

