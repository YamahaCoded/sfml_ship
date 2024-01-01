#ifndef ASTEROID_H
#define ASTEROID_H

#include <SFML/Graphics.hpp>
using namespace sf;

class Asteroid{
    public:
        Asteroid();
        void update();
        void draw(RenderWindow &w);
        void resetPos();
        bool isOutOfBounds();
        FloatRect getBounds();

    private:
        void movement();
        float spdy = 0.8f;
        float spdx;
        int randomInt(int a, int b);
        float chooseDirection();
		Texture texture;
		Sprite sprite;
};

#endif