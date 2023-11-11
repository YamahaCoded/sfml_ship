#include "player.hpp"

Player::Player(){
    //Defines player stuff like sprite, size and initial position
    if (!texture.loadFromFile("ship.png")){
    }
    sprite.setTexture(texture);
    sprite.setPosition(200.0f - 15.0f, 250.0f);
    sprite.setScale(2, 2);
}

void Player::movement(){
    //Accelerates depending on the pressed key
    if(Keyboard::isKeyPressed(Keyboard::A)){
        spd -= A;
    }
    if(Keyboard::isKeyPressed(Keyboard::D)){
        spd += A;
    }

    //Calculates friction depending on spd
    if(spd > 0.0f){
        spd -= friction;
        if(spd < 0.0f){
            spd = 0.0f;
        }
    }else if(spd < 0.0f){
        spd += friction;
        if(spd > 0.0f){
            spd = 0.0f;
        }
    }

    //Handles speed limit
    if(spd > maxSpd){
        spd = maxSpd;
    }else if(spd < -maxSpd){
        spd = -maxSpd;
    }

    //Moves the sprite along the screen
    sprite.move(spd, 0.0f);
}

void Player::warp(){
    //Checks if should warp depending on the current x position
    if(sprite.getPosition().x < -sprite.getGlobalBounds().width){
        sprite.setPosition(400.0f, sprite.getPosition().y);
    }else if(sprite.getPosition().x > 400.0f){
        sprite.setPosition(-sprite.getGlobalBounds().width, sprite.getPosition().y);
    }
}

void Player::update(){
    //Calls constantly checked functions
    warp();
    movement();
}

void Player::draw(RenderWindow &w){
    //Draw player sprite
    w.draw(sprite);
}

void Player::shoot(std::vector<Bullet> &bullets){
    //Avoids bullet spam
    if(canShoot){ 
        bullets.push_back(Bullet(sprite.getPosition().x + sprite.getGlobalBounds().width / 2, sprite.getPosition().y));
        canShoot = false; 
    }
}
