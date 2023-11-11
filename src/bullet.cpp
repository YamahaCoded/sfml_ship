#include "bullet.hpp"

Bullet::Bullet(float x, float y){
    //Sets bullet size, position and color
    shape.setRadius(2.0f);
    shape.setPosition(x-2, y);
    shape.setFillColor(Color::White);
}

void Bullet::update(){
    //Makes the bullet go up
    shape.move(0.0f, -spd);
}

void Bullet::draw(RenderWindow &w){
    //Draw bullet
    w.draw(shape);
}

bool Bullet::isOutOfBounds(){
    //Check if bullets still on screen
    return shape.getPosition().y < 0 || shape.getPosition().y > 300;
}
