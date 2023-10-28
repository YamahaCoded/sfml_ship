#include <SFML/Graphics.hpp>
#include "player.hpp"
using namespace sf;

int main(){
	RenderWindow w(VideoMode(800, 600), "hi mom");
	w.setFramerateLimit(60);
	
	Player player;

	while (w.isOpen()){
		Event event;
		while (w.pollEvent(event)){
			if(event.type == Event::Closed)
				w.close();
		}

	player.update();
	w.clear();
	player.draw(w);
	w.display();
	}
	return 0;
}
