#include "tw_will.h"

#include "will_idle.h"
#include "physics.h"

#include "input.h"

TWWill::TWWill(int x, int y) {
    m_x = x;
    m_y = y;

    m_x_speed = 0;
    m_y_speed = 0;

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

void TWWill::update_self(uint64_t dt) {
    m_x_speed = 0;
    m_texture[RUNNING]->update(dt); 

    set_x(m_x + m_x_speed);
    set_y(m_y + m_y_speed);

    m_bounding_box = Rectangle(m_x + 8, m_y + 8, 16, 16);

    print("m_state: %d\n", m_state);
    print("%d\n", m_y);

    switch (m_state) {
        case RUNNING:
            m_x_speed = 0;

            check_falling();
            check_jumping();
            break;
        case JUMPING:
            m_y_speed++;

            check_falling();
            break;
        case FALLING:
            check_running();
            break;
        default:
            break;
    }

    m_colliding = false;
}

void TWWill::check_running() {
    if (m_colliding && m_y + 16 < cur_plat->y()) {
        m_x_speed = 0;
        m_y_speed = 0;

        /* Create constant to this 16 (will_height) */
        set_y(cur_plat->y() - 16 - 1);

        m_state = RUNNING;
    } else if (m_y + 16 >= 145) {
        m_x_speed = 0;
        m_y_speed = 0;

        set_y(145 - 16 - 1);

        m_state = RUNNING;
    }
}

void TWWill::check_jumping() {
    if (pressed(BUTTON_UP)) {
        m_y_speed = -7;

        m_state = JUMPING;
    }
}

void TWWill::check_falling() {
    if(m_state == JUMPING && m_y_speed >= 0) {
        m_state = FALLING;
        m_y_speed = 2;
    } else if (m_state == RUNNING && not m_colliding) {
        m_state = FALLING;
        m_y_speed = 2;
    }
}

void TWWill::draw_self() {

}

void TWWill::on_collision(const Collidable *who) {
    if (auto platform = dynamic_cast <const TWPlatform *>(who)) {
        print("Will colidiu com plataforma\n");
        m_colliding = true;

        cur_plat = platform;

        /*if (m_state == FALLING) {
            m_y = platform->y() - 16;
            //m_y_speed = 0;

            m_state = RUNNING;

        }*/
    } else
        m_colliding = false;
}

void TWWill::set_x(int x) {
    //FIXME: Change this state to m_state 
    m_x = x;
    m_texture[RUNNING]->metadata.x = m_x;
}

void TWWill::set_y(int y) {
    m_y = y;
    m_texture[RUNNING]->metadata.y = m_y;
}

const Rectangle& TWWill::bounding_box() const {
    return m_bounding_box;
}
