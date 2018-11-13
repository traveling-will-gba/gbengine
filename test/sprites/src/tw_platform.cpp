#include "tw_platform.h"

#include "physics.h"

#include "platform.h"

TWPlatform::TWPlatform(int x, int y) {
    m_x = x;
    m_y = y;

    m_texture = new Texture(1, platformPal, platformPalLen,
                            platformTiles, platformTilesLen, _4BPP);

    m_texture->metadata.pr = 0;
    m_texture->metadata.cm = 0;
    m_texture->metadata.om = 0;
    m_texture->metadata.sh = 2;
    m_texture->metadata.sz = 1;
    m_texture->metadata.x = m_x;
    m_texture->metadata.y = m_y;

    m_bounding_box = Rectangle(x + 4, y + 16, 8, 32);

    //print("pb: %d\n", m_texture->metadata.pb);
    //print("tid: %d\n", m_texture->metadata.tid);

//    print("%d %d\n", m_x, m_y);

    Physics::get_physics()->register_object(this);
}

TWPlatform::TWPlatform(int x, int y, const Texture *texture) {
    m_x = x;
    m_y = y;

    m_texture = new Texture(texture);

    m_texture->metadata.pr = 0;
    m_texture->metadata.cm = 0;
    m_texture->metadata.om = 0;
    m_texture->metadata.sh = 2;
    m_texture->metadata.sz = 1;
    m_texture->metadata.x = m_x;
    m_texture->metadata.y = m_y;

    m_bounding_box = Rectangle(m_x + 4, m_y + 16, 8, 32);

//    print("%d %d\n", m_x, m_y);

    //print("pb: %d\n", m_texture->metadata.pb);
    //print("tid: %d\n", m_texture->metadata.tid);

    Physics::get_physics()->register_object(this);
}

void TWPlatform::update_bounding_box() {
    m_bounding_box = Rectangle(m_x + 4, m_y + 16, 8, 32);
}

void TWPlatform::update_self() {
    m_texture->metadata.x = m_x;
    m_texture->update(); 
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

Texture *TWPlatform::texture() {
    return m_texture;
}

void TWPlatform::set_x(int x) {
    m_x = x;
}
void TWPlatform::set_y(int y) {
    m_y = y;
}
