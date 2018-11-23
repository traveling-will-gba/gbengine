#ifndef TW_WILL_H
#define TW_WILL_H

#include <stdbool.h>
#include <stdio.h>

#include <vector>

#include "game_object.h"
#include "collidable.h"
#include "texture.h"

#include "tw_platform.h"

class TWWill : public GameObject, public Collidable {
    public:
        enum State { RUNNING, JUMPING, SLIDING, FALLING, GAME_OVER, PUNCHING, STOPPED, REVERSE_RUNNING };

        TWWill(int x, int y);
        void update_self(uint64_t dt);
        void draw_self();
        void on_collision(const Collidable *who);
        const Rectangle& bounding_box() const;

    private:
        int m_x, m_y;
        int m_x_speed, m_y_speed;
        vector <Texture *> m_texture;
        Rectangle m_bounding_box;

        const TWPlatform *cur_plat;

        State m_state;

        bool m_colliding;

        void check_running();
        void check_jumping();
        void check_falling();

        void set_x(int x);
        void set_y(int y);
};

#endif
