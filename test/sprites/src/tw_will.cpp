#include "tw_will.h"
#include "tw_platform.h"

#include "will_idle.h"
#include "physics.h"

#include "input.h"

TWWill::TWWill(int x, int y) {
    m_x = x;
    m_y = y;

    m_x_speed = 0;
    m_y_speed = 5;

    m_texture.resize(10);

    Texture *t = new Texture(6, will_idlePal, will_idlePalLen, will_idleTiles, will_idleTilesLen, _4BPP);

    t->metadata.pr = 0;
    t->metadata.cm = 0;
    t->metadata.om = 0;
    t->metadata.sh = 0; // square
    t->metadata.sz = 1;
    t->metadata.x = m_x;
    t->metadata.y = m_y;

    m_bounding_box = Rectangle(x + 8, y + 8, 16, 16);

    m_texture[RUNNING] = t;

    m_state = RUNNING;

    Physics::get_physics()->register_object(this);
}

void TWWill::update_self() {
    m_x_speed = 0;
    m_texture[RUNNING]->update(); 
    /*

    if (m_state == RUNNING) {
        m_x_speed = 2;
    } else
        m_x_speed = 0;

    if (m_state == JUMPING) {
        m_y_speed++;
        if(m_y_speed >= 0) {
            m_state = FALLING;
            m_y_speed = 0;
        }
    }

    if (pressed(BUTTON_UP)) {
        if (m_state == RUNNING) {
            m_state = JUMPING;
            m_y_speed = -7;
            m_x_speed = 1;
        }
    }

    if (m_state == RUNNING && not m_colliding) {
        m_state = FALLING;
    }

    if (m_state == FALLING) {
        m_y_speed = 2;
        if (m_y < 144) {
            //print("caindo\n");
    //        m_y += m_y_speed;
        } else
            m_state = RUNNING;
    } else if (m_state !=JUMPING) {
        m_y_speed = 0;
    }

    m_y += m_y_speed;
//    m_x += m_x_speed;

    m_texture[RUNNING]->metadata.x = m_x;
    m_texture[RUNNING]->metadata.y = m_y;

    m_bounding_box = Rectangle(m_x + 8, m_y + 8, 16, 16);

    m_colliding = false;
    */
}

void TWWill::draw_self() {

}

void TWWill::on_collision(const Collidable *who) {
    if (auto platform = dynamic_cast <const TWPlatform *>(who)) {
        //print("Will colidiu com plataforma\n");
        m_colliding = true;

        if (m_state == FALLING) {
            m_y = platform->y() - 16;
            //m_y_speed = 0;

            m_state = RUNNING;

        }
    } else
        m_colliding = false;
}

const Rectangle& TWWill::bounding_box() const {
    return m_bounding_box;
}
