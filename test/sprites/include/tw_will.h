#ifndef TW_WILL_H
#define TW_WILL_H

#include <stdbool.h>
#include <stdio.h>

#include <vector>

#include "game_object.h"
#include "collidable.h"
#include "texture.h"

class TWWill : public GameObject, public Collidable {
    private:
        uint32_t m_x, m_y;
        vector <Texture *> m_texture;
        Rectangle m_bounding_box;

    public:
        enum { RUNNING, JUMPING, SLIDING, FALLING, GAME_OVER, PUNCHING, STOPPED, REVERSE_RUNNING };

        TWWill(uint32_t x, uint32_t y);
        void update_self();
        void draw_self();
        void on_collision();
        const Rectangle& bounding_box() const;
};

#endif
