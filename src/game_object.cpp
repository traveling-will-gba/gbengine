#include "utils.h"

#include "game_object.h"

GameObject::~GameObject() {
    print("entrei no destrutor gameobject %u\n", m_children.size());
    while (not m_children.empty()) {
        auto *p = m_children.back();
        if (p) {
            // FIXME: WHY THIS DOESN'T WORK!?
            //p->set_parent(NULL);
        }
        m_children.pop_back();
    }
    print("saí do destrutor gameobject\n");
}

void GameObject::update(uint64_t dt) {
    for (auto child : m_children) {
        child->update(dt);
    }

    update_self(dt);
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
        if (p != this) {
            print("eita 0\n");
            p->remove_child(obj);
            print("eita 1\n");
        }
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
