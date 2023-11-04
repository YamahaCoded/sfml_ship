#include <SFML/Graphics.hpp>
#include "player.hpp"
#include "bullet.hpp"
using namespace sf;

int main(){
    RenderWindow w(VideoMode(400, 300), "Ship");
    w.setFramerateLimit(60);
    
    Player player;
    std::vector<Bullet> bullets; 

    while(w.isOpen()){
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
		if(bullets.empty()){
            player.canShoot = true; 
        }
        if(Keyboard::isKeyPressed(Keyboard::Space)){
            player.shoot(bullets);
        }

        for(auto &bullet : bullets){
            bullet.update();
        }

        bullets.erase(std::remove_if(bullets.begin(), bullets.end(), [](Bullet &bullet){
            return bullet.isOutOfBounds();
        }), bullets.end());

        w.clear();
        player.draw(w);

        for(auto &bullet : bullets){
            bullet.draw(w);
        }

        w.display();
    }
    return 0;
}
