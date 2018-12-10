#include "tw_will.h"
#include "tw_platform.h"
#include "tw_collectable.h"

#include "will_idle.h"
#include "will_jumping.h"
#include "will_sliding.h"

#include "physics.h"

#include "input.h"

const int will_width = 16;
int will_height = 16;

TWWill::TWWill(int x, int y) {
    m_x_speed = 0;
    m_y_speed = 0;

    m_texture[RUNNING] = new Texture(6, will_idlePal, will_idlePalLen, will_idleTiles, will_idleTilesLen, _4BPP);
    m_texture[SLIDING] = new Texture(6, will_slidingPal, will_slidingPalLen, will_slidingTiles, will_slidingTilesLen, _4BPP);

    m_texture[RUNNING]->metadata.aid = 0;
    m_texture[RUNNING]->metadata.pr = 0;
    m_texture[RUNNING]->metadata.cm = 0;
    m_texture[RUNNING]->metadata.om = 0;
    m_texture[RUNNING]->metadata.sh = 0; // square
    m_texture[RUNNING]->metadata.sz = 1;
    m_texture[RUNNING]->metadata.om = 0;

    m_texture[SLIDING]->metadata.aid = 0;
    m_texture[SLIDING]->metadata.pr = 0;
    m_texture[SLIDING]->metadata.cm = 0;
    m_texture[SLIDING]->metadata.om = 0;
    m_texture[SLIDING]->metadata.sh = 1;
    m_texture[SLIDING]->metadata.sz = 0;
    m_texture[SLIDING]->metadata.om = 2;

    set_x(x);
    set_y(y);

    m_bounding_box = Rectangle(m_x + will_width / 2, m_y + will_height / 2, will_width, will_height);

    m_state = RUNNING;
    m_jump_counter = 0;
    m_items_collected = 0;

    m_dead = false;

    Physics::get_physics()->register_object(this);
}

void TWWill::draw_self() {
}

void TWWill::update_self(uint64_t dt) {
    m_texture[RUNNING]->update(dt);
    m_texture[SLIDING]->update(dt);

    set_x(m_x + m_x_speed);
    set_y(m_y + m_y_speed);

    m_bounding_box = Rectangle(m_x + will_width / 2, m_y + will_height / 2, will_width, will_height);

    switch (m_state) {
        case RUNNING:
            m_jump_counter = 0;
            check_falling();
            check_jumping();
            check_sliding();
            break;
        case JUMPING:
            m_y_speed++;
            check_falling();
            break;
        case FALLING:
            check_running();
            check_jumping();
            break;
        case SLIDING:
            check_falling();
            check_sliding();
            break;
        default:
            break;
    }

    m_colliding = false;
    colliding_plats.clear();
}

void TWWill::check_running() {
    if (m_state == FALLING) {
        for (size_t i = 0; i < colliding_plats.size(); i++) {
            if (m_y + will_height >= colliding_plats[i]->y() && m_y + will_height <= colliding_plats[i]->y() + 3) {
                m_y_speed = 0;

                will_height = 16;
                set_y(colliding_plats[i]->y() - will_height);

                m_texture[RUNNING]->metadata.om = 0;
                m_texture[SLIDING]->metadata.om = 2;

                m_state = RUNNING;
                break;
            }
        }
    }
}

void TWWill::check_jumping() {
    if ((pressed(BUTTON_UP) || pressed(BUTTON_A)) && m_jump_counter < 3) {
        m_y_speed = -7;
        m_jump_counter++;
        m_state = JUMPING;
    }
}

void TWWill::check_sliding() {
    if(not pressing(BUTTON_DOWN) && not pressing(BUTTON_B)) return;

    if (m_state == FALLING) {
        for (size_t i = 0; i < colliding_plats.size(); i++) {
            if (m_y + will_height >= colliding_plats[i]->y() && m_y + will_height <= colliding_plats[i]->y() + 3) {
                m_y_speed = 0;

                will_height = 8;
                set_y(colliding_plats[i]->y() - will_height);

                m_texture[RUNNING]->metadata.om = 2;
                m_texture[SLIDING]->metadata.om = 0;

                m_state = SLIDING;
                break;
            }
        }
    }
}

void TWWill::check_falling() {
    if(m_state == JUMPING && m_y_speed >= 0) {
        m_state = FALLING;
        m_y_speed = 1;
    }else if (m_state == RUNNING) {
        m_state = FALLING;
        m_y_speed = 1;
    } else if (m_state == SLIDING) {
        m_state = FALLING;
        m_y_speed = 1;
    }
}

void TWWill::on_collision(const Collidable *who) {
    m_colliding = false;

    if (auto col = dynamic_cast <const TWCollectable *>(who)) {
        m_items_collected++;
    } else if (auto platform = dynamic_cast <const TWPlatform *>(who)) {
        m_colliding = true;

        colliding_plats.push_back(platform);
        return;
    } else if (auto Enemy = dynamic_cast <const TWEnemy *>(who)) {
        m_dead = true;
    }
}

void TWWill::set_x(int x) {
    m_x = x;
    m_texture[RUNNING]->metadata.x = m_x;
    m_texture[SLIDING]->metadata.x = m_x;

}
void TWWill::set_y(int y) {
    m_y = y;
    m_texture[RUNNING]->metadata.y = m_y;
    m_texture[SLIDING]->metadata.y = m_y;
}

void TWWill::set_speed_x(int x) {
    m_x_speed = x;
}

void TWWill::set_speed_y(int y) {
    m_y_speed = y;
}

const Rectangle& TWWill::bounding_box() const {
    return m_bounding_box;
}

uint32_t TWWill::items_collected() {
    return m_items_collected;
}
