#include <SFML/Graphics.hpp>

int main(){
    
    sf::Color background(16, 16, 16);

    sf::RenderWindow window(sf::VideoMode(800, 600), "SFML Example");
    window.setFramerateLimit(60);

    sf::Texture space_ship;
    if(!space_ship.loadFromFile("./ship.png")){
        return -1;
    }

    sf::Sprite spr_space_ship(space_ship);

    while(window.isOpen()){
        sf::Event event;
        while(window.pollEvent(event)){
            if(event.type == sf::Event::Closed){
                window.close();
            }
        }
        window.clear(background);
        window.draw(spr_space_ship);       
        window.display();
    }
    return 0;
}
