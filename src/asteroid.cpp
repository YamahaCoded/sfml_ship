#include "asteroid.hpp"
#include <random>

Asteroid::Asteroid(){
    //Loads Asteroid stuff
    if (!texture.loadFromFile("asteroid.png")){
    }

    sprite.setTexture(texture);
    sprite.setPosition(randomX(50, 350), -30);
    sprite.setScale(2, 2);
    
}

bool Asteroid::isOutOfBounds(){
    //Check Bounds
    return sprite.getPosition().x < 0 || sprite.getPosition().x > 400 || sprite.getPosition().y > 300;
}

void Asteroid::movement(){
    //Movement function
    sprite.move(0.4, spd);
}

void Asteroid::draw(RenderWindow &w){
    //Draws asteroid
    w.draw(sprite);
}

void Asteroid::update(){
    //Updates movement
    movement();
}

void Asteroid::resetPos(){
    //Resets position
    sprite.setPosition(randomX(50, 350), -30);
}

int Asteroid::randomX(int a, int b){
    //Gives a random number (only used in x)
    std::random_device rd;
    std::mt19937 mt(rd()); 

    std::uniform_int_distribution<int> dist(a, b);

    return dist(mt);
}

FloatRect Asteroid::getBounds(){
    //Checks bounds
    return sprite.getGlobalBounds();
}