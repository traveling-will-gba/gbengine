#ifndef TW_COLLECTABLE
#define TW_COLLECTABLE

#include <stdbool.h>
#include <stdio.h>

#include <vector>

#include "game_object.h"
#include "collidable.h"
#include "texture.h"

class TWCollectable : public GameObject, public Collidable {
    public:
        TWCollectable(int x, int y);
        TWCollectable(int x, int y, const Texture *texture);

        void update_self(uint64_t dt);
        void draw_self();
        bool active() const;

        void set_visibility(bool visible);

        void on_collision(const Collidable *who);
        const Rectangle& bounding_box() const;
        void update_bounding_box();

        const Texture *texture() const;

        void set_x(int x);
        void set_y(int y);

    private:
        int m_x, m_y;
        Texture *m_texture;
        Rectangle m_bounding_box;
        bool m_active;
};

#endif
