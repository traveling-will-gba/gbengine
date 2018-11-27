#include "tw_platform.h"

#include "utils.h"

#include "physics.h"

#include "platform.h"

#include "plat0.h"
#include "plat1.h"
#include "plat2.h"
#include "plat3.h"

const int platform_width = 16;
const int platform_height = 32;

TWPlatform::TWPlatform(int x, int y, bool is_floor) {
    m_textures.push_back(new Texture(1, plat0Pal, plat0PalLen, plat0Tiles, plat0TilesLen, _4BPP));

    if (not is_floor) {
        m_textures.push_back(new Texture(1, plat1Pal, plat1PalLen, plat1Tiles, plat1TilesLen, _4BPP));
        m_textures.push_back(new Texture(1, plat2Pal, plat2PalLen, plat2Tiles, plat2TilesLen, _4BPP));
        m_textures.push_back(new Texture(1, plat3Pal, plat3PalLen, plat3Tiles, plat3TilesLen, _4BPP));
    }

    platform_tiles = m_textures.size();

    for (size_t i = 0; i < platform_tiles; i++) {
        m_textures[i]->metadata.pr = 0;
        m_textures[i]->metadata.cm = 0;
        m_textures[i]->metadata.om = 0;
        m_textures[i]->metadata.sh = 2;
        m_textures[i]->metadata.sz = 2;
    }

    set_x(x);
    set_y(y);

    m_bounding_box = Rectangle(m_x + (platform_width / 2), m_y + ((platform_height * platform_tiles) / 2), platform_width, platform_height * platform_tiles);

    Physics::get_physics()->register_object(this);
}

TWPlatform::TWPlatform(int x, int y, const vector<Texture *> textures, bool is_floor) {
    platform_tiles = textures.size();

    for (size_t i = 0; i < platform_tiles; i++) {
        m_textures.push_back(new Texture(textures[i]));

        m_textures[i]->metadata.pr = 0;
        m_textures[i]->metadata.cm = 0;
        m_textures[i]->metadata.om = 0;
        m_textures[i]->metadata.sh = 2;
        m_textures[i]->metadata.sz = 2;
    }

    set_x(x);
    set_y(y);

    m_bounding_box = Rectangle(m_x + (platform_width / 2), m_y + ((platform_height * platform_tiles) / 2), platform_width, platform_height * platform_tiles);

    Physics::get_physics()->register_object(this);
}

void TWPlatform::update_bounding_box() {
    m_bounding_box = Rectangle(m_x + (platform_width / 2), m_y + ((platform_height * platform_tiles) / 2), platform_width, platform_height * platform_tiles);
}

void TWPlatform::update_self(uint64_t dt) {
    update_bounding_box();
    for (size_t i=0;i<platform_tiles;i++) {
        m_textures[i]->metadata.x = m_x;
        m_textures[i]->update(dt);
    }

    m_collectable->set_x(m_x);
}

void TWPlatform::draw_self() {

}

void TWPlatform::on_collision(const Collidable *who) {

}

const Rectangle& TWPlatform::bounding_box() const {
    return m_bounding_box;
}

const int TWPlatform::x() const {
    return m_x;
}

const int TWPlatform::y() const{
    return m_y;
}

vector<Texture*> TWPlatform::textures() {
    return m_textures;
}

void TWPlatform::set_x(int x) {
    m_x = x;
    for (size_t i = 0; i < m_textures.size(); i++) {
        m_textures[i]->metadata.x = m_x;
    }
}

void TWPlatform::set_y(int y) {
    m_y = y;

    for (size_t i = 0; i < m_textures.size(); i++) {
        m_textures[i]->metadata.y = m_y + platform_height * i;

        if (m_y + platform_height * (i + 1) >= 256) {
            // hide sprite
            m_textures[i]->metadata.om = 2;
        } else {
            m_textures[i]->metadata.om = 0;
        }
    }
}

void TWPlatform::set_collectable(TWCollectable *col) {
    m_collectable = col;
    add_child(col);
}
