#include "bullet.hpp"

Bullet::Bullet(float x, float y){
    shape.setRadius(2.0f);
    shape.setPosition(x-2, y);
    shape.setFillColor(Color::White);
}

void Bullet::update(){
    shape.move(0.0f, -speed);
}

void Bullet::draw(RenderWindow &w){
    w.draw(shape);
}

bool Bullet::isOutOfBounds(){
    return shape.getPosition().y < 0 || shape.getPosition().y > 300;
}
