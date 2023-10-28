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
		Texture texture;
		Sprite sprite;
};

#endif
