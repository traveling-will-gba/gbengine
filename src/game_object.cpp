#include "utils.h"

#include "game_object.h"

GameObject::~GameObject() {

}

void GameObject::clear_children() {
    while (not m_children.empty()) {
        m_children.back()->set_parent(nullptr);
        m_children.pop_back();
    }
}

void GameObject::update(uint64_t dt) {
    for (auto child : m_children) {
        child->update(dt);
    }

    update_self(dt);
}

void GameObject::draw() {

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

        int children_size = m_children.size();

        for(int i=0;i<children_size; i++) {
            if (m_children[i] == obj)
            {
                m_children.erase(m_children.begin() + i);
                return;
            }
        }
    }
}
