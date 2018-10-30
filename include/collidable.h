#ifndef COLLIDABLE_H
#define COLLIDABLE_H

#include "rectangle.h"

class Collidable {
    public:
        virtual void on_collision() = 0;
        virtual const Rectangle& bounding_box() const = 0;
};

#endif
