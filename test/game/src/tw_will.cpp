#include "tw_will.h"
#include "tw_platform.h"

#include "will_idle.h"
#include "physics.h"

#include "input.h"

const int will_width = 16;
const int will_height = 16;

TWWill::TWWill(int x, int y) {
    m_x_speed = 0;
    m_y_speed = 0;

    m_texture.resize(10);

    Texture *t = new Texture(6, will_idlePal, will_idlePalLen, will_idleTiles, will_idleTilesLen, _4BPP);

    t->metadata.pr = 0;
    t->metadata.cm = 0;
    t->metadata.om = 0;
    t->metadata.sh = 0; // square
    t->metadata.sz = 1;

    m_texture[RUNNING] = t;

    set_x(x);
    set_y(y);

    m_bounding_box = Rectangle(m_x + will_width / 2, m_y + will_height / 2, will_width, will_height);

    m_state = RUNNING;

    Physics::get_physics()->register_object(this);
}

void TWWill::draw_self() {
}

void TWWill::update_self(uint64_t dt) {
    m_texture[RUNNING]->update(dt); 

    set_x(m_x + m_x_speed);
    set_y(m_y + m_y_speed);

    m_bounding_box = Rectangle(m_x + will_width / 2, m_y + will_height / 2, will_width, will_height);

    switch (m_state) {
        case RUNNING:
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
    cur_plat.clear();
}

void TWWill::check_running() {
    print("check_running\n");
    for (int i = 0; i < cur_plat.size(); i++) {
        if (m_colliding) {
            print("colidindo com plataforma de y %d\n", cur_plat[i]->y());
            print("will na altura %d\n", m_y);
        }

        if (m_colliding && (m_y + will_height >= cur_plat[i]->y() && m_y + will_height <= cur_plat[i]->y() + 3)) {
            print("set_running %d\n", m_y_speed);
            m_y_speed = 0;

            set_y(cur_plat[i]->y() - will_height);

            m_state = RUNNING;
            break;
        }
    }
}

void TWWill::check_jumping() {
    print("check_jumping\n");
    if (pressed(BUTTON_UP)) {
        print("set_jumping\n");
        m_y_speed = -7;
        m_state = JUMPING;
    }
}

void TWWill::check_falling() {
    print("check_falling\n");
    if(m_state == JUMPING && m_y_speed >= 0) {
        print("set_falling\n");
        m_state = FALLING;
        m_y_speed = 2;
    } else if (m_state == RUNNING && not m_colliding) {
        print("set falling\n");
        m_state = FALLING;
        m_y_speed = 2;
    }
}

void TWWill::on_collision(const Collidable *who) {
    if (auto platform = dynamic_cast <const TWPlatform *>(who)) {
        //print("colidindo com plataforma de y %d\n", platform->y());
        //print("will na altura %d\n", m_y);
        m_colliding = true;

        cur_plat.push_back(platform);
        //cur_plat = platform;
    } else
        m_colliding = false;
}

void TWWill::set_x(int x) {
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
