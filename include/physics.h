#ifndef PHYSICS_H
#define PHYSICS_H

#include <list>

#include "collidable.h"

using std::list;

class Physics {
    public:
        static Physics *get_physics();
        static Physics *instance;

        void register_object(Collidable *);
        void unregister_object(Collidable *);
        void do_collisions();
        void set_target(Collidable *c);

        void clear_list();

    private:
        static list<Collidable *> objects;
        Collidable *target;

        bool check_collision(Collidable *, Collidable *);

        Physics(){}
};

#endif
