#ifndef PLAYER_H
#define PLAYER_H

#include <SFML/Graphics.hpp>
using namespace sf;

class Player{
	public:
		Player();
		void update();
		void draw(RenderWindow &w);
		
	private:
		float A = 0.2f;
		float spd = 0.0f;
		float maxSpd = 8.0f;
		float friction = 0.06f;
		void movement();
		void warp();
		Texture texture;
		Sprite sprite;
};

#endif
