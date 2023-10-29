#include <SFML/Graphics.hpp>
#include "player.hpp"
using namespace sf;

int main(){
	RenderWindow w(VideoMode(400, 300), "Ship");
	w.setFramerateLimit(60);
	
	Player player;

	while (w.isOpen()){
		Event event;
		while (w.pollEvent(event)){
			if(event.type == Event::Closed)
				w.close();
			if(event.type == Event::Resized){
				View view = w.getView();
				view.setSize(float (event.size.width), float (event.size.height));
				w.setView(view);
			}
			if(event.type == Event::LostFocus){
				w.waitEvent(event);
			}
		}

	player.update();
	w.clear();
	player.draw(w);
	w.display();
	}
	return 0;
}
