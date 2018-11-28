#include "tw_collectable.h"

#include "tw_will.h"

#include "col.h"

#include "physics.h"

const int col_width = 8;
const int col_height = 8;

TWCollectable::TWCollectable(int x, int y) {
    m_texture = new Texture(6, colPal, colPalLen, colTiles, colTilesLen, _4BPP);
    m_texture->metadata.pr = 0;
    m_texture->metadata.cm = 0;
    m_texture->metadata.om = 0;
    m_texture->metadata.sh = 0; // square
    m_texture->metadata.sz = 0;

    set_x(x);
    set_y(y);

    m_bounding_box = Rectangle(m_x + col_width / 2, m_y + col_height / 2, col_width, col_height);

    m_active = true;
    Physics::get_physics()->register_object(this);
}

TWCollectable::TWCollectable(int x, int y, const Texture *texture) {
    m_texture = new Texture(texture);
    m_texture->metadata.pr = 0;
    m_texture->metadata.cm = 0;
    m_texture->metadata.om = 0;
    m_texture->metadata.sh = 0; // square
    m_texture->metadata.sz = 0;

    set_x(x);
    set_y(y);

    m_bounding_box = Rectangle(m_x + col_width / 2, m_y + col_height / 2, col_width, col_height);

    m_active = true;
    Physics::get_physics()->register_object(this);
}

void TWCollectable::set_visibility(bool visible) {
    if (visible) {
        m_texture->metadata.om = 0;
        m_active = true;
    } else {
        m_texture->metadata.om = 2;
        m_active = false;
    }
}

const Texture *TWCollectable::texture() const {
    return m_texture;
}

void TWCollectable::update_self(uint64_t dt) {
    update_bounding_box();
    m_texture->update(dt);
}

void TWCollectable::draw_self() {

}

bool TWCollectable::active() const {
    return m_active;
}

void TWCollectable::on_collision(const Collidable *who) {
    if (auto will = dynamic_cast <const TWWill *>(who)) {
        set_visibility(false);
    }
}

void TWCollectable::set_x(int x) {
    m_x = x;
    m_texture->metadata.x = m_x;

}
void TWCollectable::set_y(int y) {
    m_y = y;
    m_texture->metadata.y = m_y;
}

const Rectangle& TWCollectable::bounding_box() const {
    return m_bounding_box;
}

void TWCollectable::update_bounding_box() {
    m_bounding_box = Rectangle(m_x + col_width / 2, m_y + col_height / 2, col_width, col_height);
}
