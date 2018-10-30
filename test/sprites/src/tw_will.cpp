#include "tw_will.h"
#include "will_idle.h"
#include "physics.h"

TWWill::TWWill(uint32_t x, uint32_t y) {
    this->m_x = x;
    this->m_y = y;

    m_texture.resize(10);

    Texture *t = new Texture(6, will_idlePal, will_idlePalLen, will_idleTiles, will_idleTilesLen, _4BPP);

    t->metadata.pr = 0;
    t->metadata.cm = 0;
    t->metadata.om = 0;
    t->metadata.sh = 0; // square
    t->metadata.sz = 1;
    t->metadata.x = x;
    t->metadata.y = y;

    m_bounding_box = Rectangle(x + 8, y + 8, 16, 16);

    m_texture[RUNNING] = t;

    Physics::get_physics()->register_object(this);
}

void TWWill::update_self() {
    m_texture[RUNNING]->update(); 
}

void TWWill::draw_self() {

}

void TWWill::on_collision() {
    print("Colidi o/\n");
}

const Rectangle& TWWill::bounding_box() const {
    return m_bounding_box;
}
