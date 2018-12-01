#include "tw_collectable.h"

#include "tw_will.h"

#include "utils.h"
#include "physics.h"

#include "level1_item.h"
#include "level2_item.h"
#include "level3_item.h"
#include "level4_item.h"
#include "level5_item.h"
#include "level6_item.h"

const int col_width = 8;
const int col_height = 8;

TWCollectable::TWCollectable(int level, int x, int y) {
    load_collectable_texture(level);

    m_texture->metadata.aid = 0;
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

    m_texture->metadata.aid = 0;
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

TWCollectable::~TWCollectable() {
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

void TWCollectable::load_collectable_texture(int level) {
    switch(level) {
        case LEVEL_MENU:
        case MENU_DEFEAT:
        case MENU_VICTORY:
            // do nothing
            break;
        case LEVEL_1:
            m_texture = new Texture(6, level1_itemPal, level1_itemPalLen, level1_itemTiles, level1_itemTilesLen, _4BPP);
            break;
        case LEVEL_2:
            m_texture = new Texture(6, level2_itemPal, level2_itemPalLen, level2_itemTiles, level2_itemTilesLen, _4BPP);
            break;
        case LEVEL_3:
            m_texture = new Texture(8, level3_itemPal, level3_itemPalLen, level3_itemTiles, level3_itemTilesLen, _4BPP);
            break;
        case LEVEL_4:
            m_texture = new Texture(6, level4_itemPal, level4_itemPalLen, level4_itemTiles, level4_itemTilesLen, _4BPP);
            break;
        case LEVEL_5:
            m_texture = new Texture(6, level5_itemPal, level5_itemPalLen, level5_itemTiles, level5_itemTilesLen, _4BPP);
            break;
        case LEVEL_6:
            m_texture = new Texture(6, level6_itemPal, level6_itemPalLen, level6_itemTiles, level6_itemTilesLen, _4BPP);
            break;
    }
}
