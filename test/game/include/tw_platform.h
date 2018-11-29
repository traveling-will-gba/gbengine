#ifndef TW_PLATFORM_H
#define TW_PLATFORM_H

#include "game_object.h"
#include "collidable.h"
#include "texture.h"

#include "tw_collectable.h"

#include <stdio.h>

class TWPlatform : public GameObject, public Collidable {
    public:
        TWPlatform(int level, int x, int y, bool is_floor = false);
        TWPlatform(int x, int y, const vector<Texture*> textures, bool is_floor = false);

        void update_self(uint64_t dt);
        void draw_self();
        bool active() const { return true; }

        void on_collision(const Collidable *who);
        const Rectangle& bounding_box() const;
        void update_bounding_box();

        void set_x(int x);
        void set_y(int y);

        const int x() const;
        const int y() const;

        vector<Texture*> textures();

        void set_collectable(TWCollectable *col);
        TWCollectable *collectable();

    private:
        vector<Texture*> m_textures;
        TWCollectable *m_collectable;
        int m_x, m_y;
        int platform_tiles;
        Rectangle m_bounding_box;
        bool m_is_floor;

        void load_platforms(int level);
};

#endif
