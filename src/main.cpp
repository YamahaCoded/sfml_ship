#include <SFML/Graphics.hpp>
#include "player.hpp"
#include "bullet.hpp"
#include "asteroid.hpp"
using namespace sf;

int main(){
    //Render window and limit fps
    RenderWindow w(VideoMode(400, 300), "Ship");
    w.setFramerateLimit(60);

    //Creates the player and the bullets he will shoot
    Player player;
    std::vector<Bullet> bullets; 
    Asteroid asteroid;

    //Handles window events, like closing, losing focus and resizing (this last one still terrible, i'll try to fix in the future)
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

        //Call player update function
        player.update();

        //Avoid bullet spam
		if(bullets.empty()){
            player.canShoot = true; 
        }
        
        //Check if space is pressed to shoot bullets, updates bullets and erase them if they are out of bounds
        if(Keyboard::isKeyPressed(Keyboard::Space)){
            player.shoot(bullets);
        }

        for(auto &bullet : bullets){
            bullet.update();
        }

        bullets.erase(std::remove_if(bullets.begin(), bullets.end(), [](Bullet &bullet){
            return bullet.isOutOfBounds();
        }), bullets.end());

        if(asteroid.isOutOfBounds() == true){
            asteroid.resetPos();
        }

        //Updates Asteroid
        asteroid.update();

        //Checks Collisions
        auto bulletIt = bullets.begin();
        for(auto &bullet : bullets){
            FloatRect bulletBounds = bullet.getBounds();
            FloatRect asteroidBounds = asteroid.getBounds();

            if(bulletBounds.intersects(asteroidBounds)){
                asteroid.resetPos();
                bulletIt = bullets.erase(bulletIt);
            }
        }


        //Clear window
        w.clear();

        //Draw stuff if needed
        player.draw(w);
        asteroid.draw(w);

        for(auto &bullet : bullets){
            bullet.draw(w);
        }

        //Displays window
        w.display();
    }
    return 0;
}
