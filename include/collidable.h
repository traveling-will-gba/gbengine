#ifndef COLLIDABLE_H
#define COLLIDABLE_H

#include "rectangle.h"

class Collidable {
    public:
        virtual ~Collidable() = default;
        virtual void on_collision(const Collidable *who) = 0;
        virtual const Rectangle& bounding_box() const = 0;
        virtual bool active() const = 0;
};

#endif
