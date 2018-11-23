#ifndef TW_PLATFORM_H
#define TW_PLATFORM_H

#include "game_object.h"
#include "collidable.h"
#include "texture.h"

#include <stdio.h>

class TWPlatform : public GameObject, public Collidable {
    public:
        TWPlatform(int x, int y);
        TWPlatform(int x, int y, const vector<Texture*> textures);

        void update_self(uint64_t dt);
        void draw_self();
        void on_collision(const Collidable *who);
        const Rectangle& bounding_box() const;
        void update_bounding_box();
        void set_x(int x);
        void set_y(int y);

        const int x() const;
        const int y() const;
        vector<Texture*> textures();

    private:
        vector<Texture*> m_textures;
        int m_x, m_y;
        Rectangle m_bounding_box;
};

#endif
