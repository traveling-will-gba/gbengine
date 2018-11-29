#include "tw_will.h"
#include "tw_platform.h"
#include "tw_collectable.h"

#include "will_idle.h"
#include "will_jumping.h"

#include "physics.h"

#include "input.h"

const int will_width = 16;
const int will_height = 16;

TWWill::TWWill(int x, int y) {
    m_x_speed = 0;
    m_y_speed = 0;

    m_texture = new Texture(6, will_idlePal, will_idlePalLen, will_idleTiles, will_idleTilesLen, _4BPP);

    m_texture->metadata.aid = 0;
    m_texture->metadata.pr = 0;
    m_texture->metadata.cm = 0;
    m_texture->metadata.om = 0;
    m_texture->metadata.sh = 0; // square
    m_texture->metadata.sz = 1;

    set_x(x);
    set_y(y);

    m_bounding_box = Rectangle(m_x + will_width / 2, m_y + will_height / 2, will_width, will_height);

    m_state = RUNNING;
    m_jump_counter = 0;
    m_items_collected = 0;

    Physics::get_physics()->register_object(this);
}

void TWWill::draw_self() {
}

void TWWill::update_self(uint64_t dt) {
    m_texture->update(dt);

    set_x(m_x + m_x_speed);
    set_y(m_y + m_y_speed);

    m_bounding_box = Rectangle(m_x + will_width / 2, m_y + will_height / 2, will_width, will_height);

    switch (m_state) {
        case RUNNING:
            m_jump_counter = 0;
            check_falling();
            check_jumping();
            break;
        case JUMPING:
            m_y_speed++;
            check_falling();
            break;
        case FALLING:
            check_running();
            check_jumping();
            break;
        default:
            break;
    }

    m_colliding = false;
    colliding_plats.clear();
}

void TWWill::check_running() {
    // print("check_running\n");
    for (size_t i = 0; i < colliding_plats.size(); i++) {
        //if (m_colliding) {
            // print("colidindo com plataforma de y %d\n", colliding_plats[i]->y());
            // print("will na altura %d\n", m_y);
        //}

        if (/*m_colliding &&*/ (m_y + will_height >= colliding_plats[i]->y() && m_y + will_height <= colliding_plats[i]->y() + 3)) {
            // print("set_running %d\n", m_y_speed);

            m_y_speed = 0;

            set_y(colliding_plats[i]->y() - will_height);

            m_state = RUNNING;
            break;
        }
    }
}

void TWWill::check_jumping() {
    // print("check_jumping\n");
    if (pressed(BUTTON_UP) && m_jump_counter < 3) {
        // print("set_jumping\n");
        m_y_speed = -7;
        m_jump_counter++;
        m_state = JUMPING;
    }
}

void TWWill::check_falling() {
    // print("check_falling\n");
    if(m_state == JUMPING && m_y_speed >= 0) {
        // print("set_falling\n");
        m_state = FALLING;
        m_y_speed = 2;
    } else if (m_state == RUNNING) {
        // print("set falling\n");
        m_state = FALLING;
        m_y_speed = 2;
    }
}

void TWWill::on_collision(const Collidable *who) {
    m_colliding = false;

    if (auto col = dynamic_cast <const TWCollectable *>(who)) {
        // print("Colidiu com coletavel\n");
        m_items_collected++;
        // print("COLETAVEIS PEGOS %d\n", m_items_collected);
    } else if (auto platform = dynamic_cast <const TWPlatform *>(who)) {
        // print("Colidiu com plataforma\n");
        m_colliding = true;

        colliding_plats.push_back(platform);
        return;
    }
}

void TWWill::set_x(int x) {
    m_x = x;
    m_texture->metadata.x = m_x;

}
void TWWill::set_y(int y) {
    m_y = y;
    m_texture->metadata.y = m_y;
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
