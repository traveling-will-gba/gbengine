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
        bool active() const { return true; }

        void on_collision(const Collidable *who);
        const Rectangle& bounding_box() const;

        uint32_t items_collected();

        void set_speed_x(int x);
        void set_speed_y(int y);

        const int x() const { return m_x; }
        const int y() const { return m_y; }
        const int speed_x() const { return m_x_speed; }
        const int speed_y() const { return m_y_speed; }

    private:
        int m_x, m_y;
        int m_x_speed, m_y_speed;
        int m_jump_counter;
        Texture *m_texture;
        Rectangle m_bounding_box;

        uint32_t m_items_collected;

        //vector <const TWPlatform *> cur_plat;

        vector <const TWPlatform *> colliding_plats;

        State m_state;

        bool m_colliding;

        void check_running();
        void check_jumping();
        void check_falling();

        void set_x(int x);
        void set_y(int y);
};

#endif
