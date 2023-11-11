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
        float spd = 0.8f;
        int randomX(int a, int b);
		Texture texture;
		Sprite sprite;
};

#endif