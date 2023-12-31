#ifndef BULLET_H
#define BULLET_H

#include <SFML/Graphics.hpp>
using namespace sf;

class Bullet{
    public:
        Bullet(float x, float y);
        void update();
        void draw(RenderWindow &w);
        bool isOutOfBounds();
        FloatRect getBounds();

    private:
        float spd = 5.0f;
        CircleShape shape;
};

#endif
