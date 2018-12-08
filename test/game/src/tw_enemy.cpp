#include "tw_enemy.h"

#include "physics.h"

#include "enemy1.h"

const int enemy_width = 16;
const int enemy_height = 16;

TWEnemy::TWEnemy(int x, int y) {
    m_texture = new Texture(6, enemy1Pal, enemy1PalLen, enemy1Tiles, enemy1TilesLen, _4BPP);

    m_texture->metadata.aid = 0;
    m_texture->metadata.pr = 0;
    m_texture->metadata.cm = 0;
    m_texture->metadata.om = 0;
    m_texture->metadata.sh = 0;
    m_texture->metadata.sz = 1;

    set_x(x);
    set_y(y);

    m_bounding_box = Rectangle(m_x + enemy_width / 2, m_y + enemy_height / 2, enemy_width, enemy_height);

    m_active = true;
    Physics::get_physics()->register_object(this);
}

TWEnemy::TWEnemy(int x, int y, const Texture *texture) {
    m_texture = new Texture(texture);

    m_texture->metadata.aid = 0;
    m_texture->metadata.pr = 0;
    m_texture->metadata.cm = 0;
    m_texture->metadata.om = 0;
    m_texture->metadata.sh = 0; // square
    m_texture->metadata.sz = 1;

    set_x(x);
    set_y(y);

    m_bounding_box = Rectangle(m_x + enemy_width / 2, m_y + enemy_height / 2, enemy_width, enemy_height);

    m_active = true;
    Physics::get_physics()->register_object(this);
}

TWEnemy::~TWEnemy() {
}

void TWEnemy::set_x(int x) {
    m_x = x;
    m_texture->metadata.x = m_x;

}
void TWEnemy::set_y(int y) {
    m_y = y;
    m_texture->metadata.y = m_y;
}

void TWEnemy::update_self(uint64_t dt) {
    update_bounding_box();
    m_texture->update(dt);
}

void TWEnemy::draw_self() {

}

bool TWEnemy::active() const {
    return m_active;
}

void TWEnemy::set_visibility(bool visible) {
    if (visible) {
        m_texture->metadata.om = 0;
        m_active = true;
    } else {
        m_texture->metadata.om = 2;
        m_active = false;
    }
}

const Texture *TWEnemy::texture() const {
    return m_texture;
}

void TWEnemy::on_collision(const Collidable *who) {
    //print("colidindo com alguém\n");
 /*   if (auto will = dynamic_cast <const TWWill *>(who)) {
        set_visibility(false);
    }*/
}

const Rectangle& TWEnemy::bounding_box() const {
    return m_bounding_box;
}

void TWEnemy::update_bounding_box() {
    m_bounding_box = Rectangle(m_x + enemy_width / 2, m_y + enemy_height / 2, enemy_width, enemy_height);
}
