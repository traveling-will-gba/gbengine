#include "physics.h"
#include "utils.h"

Physics* Physics::instance;
list <Collidable *> Physics::objects;

Physics *Physics::get_physics() {
    if (!instance) {
        instance = new Physics();
    }

    return instance;
}

void Physics::register_object(Collidable *c) {
    objects.emplace_back(c);
}

void Physics::unregister_object(Collidable *c) {
    objects.remove(c);
}

bool Physics::check_collision(Collidable *a, Collidable *b) {
    if (not a) print("A nulo\n");
    if (not b) print("B nulo\n");
    if (not a || not b) return false;
    auto bbA = a->bounding_box();
    auto bbB = b->bounding_box();

    /*auto r = bbA.intersection(bbB);

    print("Area: %f\n", r.area());

    return r.area() > 0;*/
    return bbA.intersection(bbB);
}

void Physics::clear_list() {
    objects.clear();
}

void Physics::do_collisions() {
    for (auto obj : objects) {
        if (obj == target or not obj->active() or not target->active()) continue;

        if (check_collision(target, obj)) {
            target->on_collision(obj);
            obj->on_collision(target);
        }
    }
}

void Physics::set_target(Collidable *c) {
    this->target = c;
}
