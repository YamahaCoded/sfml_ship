#include "player.hpp"

Player::Player(){
	if(!texture.loadFromFile("ship.png")){
	}
	sprite.setTexture(texture);
	sprite.setPosition(200.0f - 15.0f, 250.0f);
	sprite.setScale(2, 2);
}

void Player::movement(){
	if(Keyboard::isKeyPressed(Keyboard::A)){
		spd -= A;
	}
	if(Keyboard::isKeyPressed(Keyboard::D)){
		spd += A;
	}

    if(spd > 0.0f){
        spd -= friction;
        if(spd < 0.0f){
            spd = 0.0f;
        }
    } else if(spd < 0.0f){
        spd += friction;
        if(spd > 0.0f){
            spd = 0.0f;
        }
    }

    if(spd > maxSpd){
        spd = maxSpd;
    } else if(spd < -maxSpd){
        spd = -maxSpd;
    }

	sprite.move(spd, 0.0f);
}

void Player::warp(){
	if (sprite.getPosition().x < -sprite.getGlobalBounds().width) {
        sprite.setPosition(400.0f, sprite.getPosition().y);
    } else if (sprite.getPosition().x > 400.0f) {
        sprite.setPosition(-sprite.getGlobalBounds().width, sprite.getPosition().y);
    }
}

void Player::update(){
	warp();
	movement();
}

void Player::draw(RenderWindow &w){
	w.draw(sprite);
}
