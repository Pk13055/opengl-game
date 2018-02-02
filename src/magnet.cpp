/*
	magnet functionality

*/

#include <cmath>
#include <utility>
#include "main.h"
#include "magnet.h"

Magnet::Magnet(float x, float y, color_t color)
: Trampoline(x, y, color) {
	this->rotation = -90;
}
