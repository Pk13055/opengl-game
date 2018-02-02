#include "trampoline.h"
#include "main.h"

#ifndef MAGNET_H
#define MAGNET_H

class Magnet : public Trampoline {
public:
	Magnet(float x, float y, color_t color);
private:
	VAO *object;
};

#endif  // MAGNET_HH
