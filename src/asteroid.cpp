#include "asteroid.hpp"
#include <random>

Asteroid::Asteroid(){
    //Loads Asteroid stuff
    if(!texture.loadFromFile("./resources/asteroid.png")){
    }

    sprite.setTexture(texture);
    sprite.setPosition(randomInt(50, 350), -sprite.getGlobalBounds().height - 65);
    sprite.setScale(2, 2);
    chooseDirection();
}

bool Asteroid::isOutOfBounds(){
    //Check Bounds
    return sprite.getPosition().x < -40 || sprite.getPosition().x > 400 || sprite.getPosition().y > 300;
}

void Asteroid::movement(){
    //Movement function
    sprite.move(spdx, spdy);
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
    sprite.setPosition(randomInt(100, 300), -sprite.getGlobalBounds().height - 65);
    chooseDirection();
}

int Asteroid::randomInt(int a, int b){
    //Gives a random number (only used in x)
    std::random_device rd;
    std::mt19937 mt(rd()); 

    std::uniform_int_distribution<int> dist(a, b);

    return dist(mt);
}

float Asteroid::chooseDirection(){
    //Changes asteroid direction
    int r = randomInt(0, 1);
    if(r == 0){
        spdx = 0.4;
    }else{
        spdx = -0.4;
    }
    return spdx;
}

FloatRect Asteroid::getBounds(){
    //Checks bounds
    return sprite.getGlobalBounds();
}