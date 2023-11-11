#include "asteroid.hpp"
#include <random>

Asteroid::Asteroid(){
    if (!texture.loadFromFile("asteroid.png")){
    }

    sprite.setTexture(texture);
    sprite.setPosition(randomX(50, 350), -30);
    sprite.setScale(2, 2);
}

bool Asteroid::isOutOfBounds(){
    return sprite.getPosition().x < 0 || sprite.getPosition().x > 400 || sprite.getPosition().y > 300;
}

void Asteroid::movement(){
    sprite.move(0.4, spd);
}

void Asteroid::draw(RenderWindow &w){
    w.draw(sprite);
}

void Asteroid::update(){
    movement();
}

void Asteroid::resetPos(){
    sprite.setPosition(randomX(50, 350), -30);
}

int Asteroid::randomX(int a, int b){
    std::random_device rd;
    std::mt19937 mt(rd()); 

    std::uniform_int_distribution<int> dist(a, b);

    return dist(mt);
}