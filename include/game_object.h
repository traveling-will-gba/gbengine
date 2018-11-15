#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H

#include <vector>

using std::vector;

class GameObject {
    protected:
        GameObject *m_parent;
        int m_x, m_y;
        int m_speed_x, m_speed_y;
        vector <GameObject *> m_children;

        GameObject *parent() const { return m_parent; }

        virtual void update_self() = 0;
        virtual void draw_self() = 0;

    public:
        void update();
        void draw();

        void set_parent(GameObject *obj) { m_parent = obj; }
        void add_child(GameObject *);
        void remove_child(GameObject *);
};

#endif
