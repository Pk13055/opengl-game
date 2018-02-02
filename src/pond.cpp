/*
	function definitions for
	pond class
*/
#include "main.h"
#define POND 3
#define POND_WIDTH 3.5f
#include "pond.h"


Pond::Pond(float x, float y, color_t color, float radius = POND_WIDTH) {
    this->position = glm::vec3(x, y, 0);
    this->radius = radius;

    double total_shapes = 18;
    GLfloat vertex_buffer_data[(int) total_shapes * 3 * 3] = {};

    // contains the edge points
    vector< pair<double, double> > points;
    double angle = 1.0f / total_shapes * M_PI, init_angle = angle;
    for(int shapes = 1; shapes <= total_shapes; shapes++) {
        double cur_angle = init_angle -= angle;
        points.push_back(make_pair(radius * cos(cur_angle), radius * sin(cur_angle)));
    }
    int i = 0;
    bool first = true;
    points.push_back(points.front()), points.push_back(points.front());
    for(auto point: points) {
        vertex_buffer_data[i++] = point.first;
        vertex_buffer_data[i++] = point.second;
        vertex_buffer_data[i++] = 0.0f;

        if(!first && point == points.back()) break;

        vertex_buffer_data[i++] = 0.0f;
        vertex_buffer_data[i++] = 0.0f;
        vertex_buffer_data[i++] = 0.0f;

        if(!first) {
            vertex_buffer_data[i++] = point.first;
            vertex_buffer_data[i++] = point.second;
            vertex_buffer_data[i++] = 0.0f;
        }
        first = false;
    }

    this->object = create3DObject(GL_TRIANGLES, total_shapes * 3, vertex_buffer_data, color, GL_FILL);
}

void Pond::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 0, 1));
    rotate          = rotate * glm::translate(glm::vec3(0, 0, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}

void Pond::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

bounding_box_t Pond::bounding_box() {
    float x = this->position.x, y = this->position.y;
    bounding_box_t bbox = { x, y, (double) this->radius, POND };
    return bbox;
}
