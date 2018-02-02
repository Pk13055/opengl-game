/*

	function and constructor definitions for the porcupine class

*/

#include <cmath>
#include <utility>
#include "main.h"
#include "porcupine.h"

Porcupine::Porcupine(float x, float y, float length, float width, color_t color) {
	this->set_position(x, y);

	this->xspeed = 0.005f;
	this->yspeed = 0;
	this->color = color;
	this->rotation = 0.0f;
	this->length = length;
	this->width = width;
	this->original = this->position;

	int total_shapes = 4, i = 0;
	float per_triangle_length = length / (float) total_shapes;


	GLfloat vertex_buffer_data[(int) total_shapes * 3 * 3];
	float start_point = - this->length / 2.0f;
	float cur_point = start_point;
	for(int i = 0, shapes = 1; shapes <= total_shapes; shapes++) {

		vertex_buffer_data[i++] = cur_point;
		vertex_buffer_data[i++] = 0.0f;
		vertex_buffer_data[i++] = 0.0f;

		vertex_buffer_data[i++] = cur_point + per_triangle_length / 2.0f;
		vertex_buffer_data[i++] = width;
		vertex_buffer_data[i++] = 0.0f;

		vertex_buffer_data[i++] = cur_point + per_triangle_length;
		vertex_buffer_data[i++] = 0.0f;
		vertex_buffer_data[i++] = 0.0f;

		cur_point += per_triangle_length;
	}


	this->object = create3DObject(GL_TRIANGLES, total_shapes * 3, vertex_buffer_data, color, GL_FILL);
}

void Porcupine::tick() {
    this->position.x -= this->xspeed;
    if(fabs(this->position.x - this->original.x) > this->length)
        this->xspeed *= -1;
}

void Porcupine::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 0, 1));
    rotate          = rotate * glm::translate(glm::vec3(0, 0, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}

void Porcupine::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

bounding_box_t Porcupine::bounding_box() {
    float x = this->position.x, y = this->position.y;
    bounding_box_t bbox = { x, y };
    bbox.role = RECTANGLE;
    bbox.rotation = this->rotation;
    bbox.size = make_pair(this->length, this->width);
    return bbox;
}
