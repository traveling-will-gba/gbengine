#include "tw_platform.h"

#include "utils.h"
#include "physics.h"

#include "level1_plat0.h"
#include "level1_plat1.h"
#include "level1_plat2.h"
#include "level1_plat3.h"

#include "level2_plat0.h"
#include "level2_plat1.h"
#include "level2_plat2.h"
#include "level2_plat3.h"

const int platform_width = 16;
const int platform_height = 32;

const int collectable_width = 8;

TWPlatform::TWPlatform(int level, int x, int y, bool is_floor) {
    m_is_floor = is_floor;

    load_platforms(level);

    platform_tiles = m_textures.size();

    for (size_t i = 0; i < platform_tiles; i++) {
        m_textures[i]->metadata.aid = 0;
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

        m_textures[i]->metadata.aid = 0;
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

    m_collectable->set_x(m_x + platform_width / 2 - collectable_width / 2);
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

TWCollectable *TWPlatform::collectable() {
    return m_collectable;
}

void TWPlatform::load_platforms(int level) {
    switch(level) {
        case 0:
            // do nothing
        case 1:
            m_textures.push_back(new Texture(1, level1_plat0Pal, level1_plat0PalLen, level1_plat0Tiles, level1_plat0TilesLen, _4BPP));

            if (not m_is_floor)
            {
                m_textures.push_back(new Texture(1, level1_plat1Pal, level1_plat1PalLen, level1_plat1Tiles, level1_plat1TilesLen, _4BPP));
                m_textures.push_back(new Texture(1, level1_plat2Pal, level1_plat2PalLen, level1_plat2Tiles, level1_plat2TilesLen, _4BPP));
                m_textures.push_back(new Texture(1, level1_plat3Pal, level1_plat3PalLen, level1_plat3Tiles, level1_plat3TilesLen, _4BPP));
            }

            break;
        case 2:
            m_textures.push_back(new Texture(1, level2_plat0Pal, level2_plat0PalLen, level2_plat0Tiles, level2_plat0TilesLen, _4BPP));

            if (not m_is_floor)
            {
                m_textures.push_back(new Texture(1, level2_plat1Pal, level2_plat1PalLen, level2_plat1Tiles, level2_plat1TilesLen, _4BPP));
                m_textures.push_back(new Texture(1, level2_plat2Pal, level2_plat2PalLen, level2_plat2Tiles, level2_plat2TilesLen, _4BPP));
                m_textures.push_back(new Texture(1, level2_plat3Pal, level2_plat3PalLen, level2_plat3Tiles, level2_plat3TilesLen, _4BPP));
            }
            break;
        case 3:
            // m_textures.push_back(new Texture(1, level3_plat0Pal, level3_plat0PalLen, level3_plat0Tiles, level3_plat0TilesLen, _4BPP));

            // if (not m_is_floor)
            // {
            //     m_textures.push_back(new Texture(1, level3_plat1Pal, level3_plat1PalLen, level3_plat1Tiles, level3_plat1TilesLen, _4BPP));
            //     m_textures.push_back(new Texture(1, level3_plat2Pal, level3_plat2PalLen, level3_plat2Tiles, level3_plat2TilesLen, _4BPP));
            //     m_textures.push_back(new Texture(1, level3_plat3Pal, level3_plat3PalLen, level3_plat3Tiles, level3_plat3TilesLen, _4BPP));
            // }
            break;
        case 4:
            // m_textures.push_back(new Texture(1, level4_plat0Pal, level4_plat0PalLen, level4_plat0Tiles, level4_plat0TilesLen, _4BPP));

            // if (not m_is_floor)
            // {
            //     m_textures.push_back(new Texture(1, level4_plat1Pal, level4_plat1PalLen, level4_plat1Tiles, level4_plat1TilesLen, _4BPP));
            //     m_textures.push_back(new Texture(1, level4_plat2Pal, level4_plat2PalLen, level4_plat2Tiles, level4_plat2TilesLen, _4BPP));
            //     m_textures.push_back(new Texture(1, level4_plat3Pal, level4_plat3PalLen, level4_plat3Tiles, level4_plat3TilesLen, _4BPP));
            // }
            break;
        case 5:
            // m_textures.push_back(new Texture(1, level5_plat0Pal, level5_plat0PalLen, level5_plat0Tiles, level5_plat0TilesLen, _4BPP));

            // if (not m_is_floor)
            // {
            //     m_textures.push_back(new Texture(1, level5_plat1Pal, level5_plat1PalLen, level5_plat1Tiles, level5_plat1TilesLen, _4BPP));
            //     m_textures.push_back(new Texture(1, level5_plat2Pal, level5_plat2PalLen, level5_plat2Tiles, level5_plat2TilesLen, _4BPP));
            //     m_textures.push_back(new Texture(1, level5_plat3Pal, level5_plat3PalLen, level5_plat3Tiles, level5_plat3TilesLen, _4BPP));
            // }
            break;
        case 6:
            // m_textures.push_back(new Texture(1, level6_plat0Pal, level6_plat0PalLen, level6_plat0Tiles, level6_plat0TilesLen, _4BPP));

            // if (not m_is_floor)
            // {
            //     m_textures.push_back(new Texture(1, level6_plat1Pal, level6_plat1PalLen, level6_plat1Tiles, level6_plat1TilesLen, _4BPP));
            //     m_textures.push_back(new Texture(1, level6_plat2Pal, level6_plat2PalLen, level6_plat2Tiles, level6_plat2TilesLen, _4BPP));
            //     m_textures.push_back(new Texture(1, level6_plat3Pal, level6_plat3PalLen, level6_plat3Tiles, level6_plat3TilesLen, _4BPP));
            // }
            break;
        default:
            break;
    }

}