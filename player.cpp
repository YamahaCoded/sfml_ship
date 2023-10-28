#include "player.hpp"

Player::Player(){
	if(!texture.loadFromFile("ship.png")){
	}
	sprite.setTexture(texture);
	sprite.setPosition(400, 300);
}

void Player::update(){

}

void Player::draw(RenderWindow &w){
	w.draw(sprite);
}
