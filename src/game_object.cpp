#include "game_object.h"

void GameObject::update() {
    for (auto child : m_children) {
        child->update();
    }

    update_self();
}

void GameObject::draw() {
    draw_self();

    for (auto child : m_children) {
        child->draw();
    }
}

void GameObject::add_child(GameObject *obj) {
    if (not obj) return;

    auto p = obj->parent();

    if (p) {
        if (p != this)
            p->remove_child(obj);
        else
            return;
    }

    m_children.push_back(obj);
    obj->set_parent(this);
}

void GameObject::remove_child(GameObject *obj) {
    if (obj) {
        obj->set_parent(nullptr);
        for (auto it = m_children.begin(); it != m_children.end(); it++) {
            if (*it == obj) {
                m_children.erase(it);
                return;
            }
        }
    }
}
