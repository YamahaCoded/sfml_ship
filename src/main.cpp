#include <SFML/Graphics.hpp>
#include "player.hpp"
#include "bullet.hpp"
#include "asteroid.hpp"
using namespace sf;

enum GameState{
    MENU,
    GAME,
    PAUSE,
    GAMEOVER
};

void menu(RenderWindow &w){
    //Loads font and draw text on screen
    Font font;
    if(!font.loadFromFile("./resources/PressStart2P-Regular.ttf")){
    }

    Text shipText;
    shipText.setFont(font);
    shipText.setCharacterSize(40);
    shipText.setFillColor(Color::White);
    shipText.setString("Ship!");
    shipText.setPosition(110, 100);

    Text startText;
    startText.setFont(font);
    startText.setCharacterSize(10);
    startText.setFillColor(Color::White);
    startText.setString("Press Enter to Start");
    startText.setPosition(100, 160);
    
    w.clear();
    w.draw(shipText);
    w.draw(startText);
    w.display();
}

void pause(RenderWindow &w){
    //Loads font and draw text on screen
    Font font;
    if(!font.loadFromFile("./resources/PressStart2P-Regular.ttf")){
    }

    Text pauseText;
    pauseText.setFont(font);
    pauseText.setCharacterSize(40);
    pauseText.setFillColor(Color::White);
    pauseText.setString("Paused!");
    pauseText.setPosition(70, 100);

    Text resumeText;
    resumeText.setFont(font);
    resumeText.setCharacterSize(10);
    resumeText.setFillColor(Color::White);
    resumeText.setString("Press Enter to Resume");
    resumeText.setPosition(90, 160);


    w.clear();
    w.draw(pauseText);
    w.draw(resumeText);
    w.display();
}

void gameover(RenderWindow &w){
    //Loads font and draw text on screen
    Font font;
    if(!font.loadFromFile("./resources/PressStart2P-Regular.ttf")){
    }

    Text gameoverText;
    gameoverText.setFont(font);
    gameoverText.setCharacterSize(40);
    gameoverText.setFillColor(Color::White);
    gameoverText.setString("GameOver");
    gameoverText.setPosition(45, 100);

    Text pressEnterText;
    pressEnterText.setFont(font);
    pressEnterText.setCharacterSize(10);
    pressEnterText.setFillColor(Color::White);
    pressEnterText.setString("Press Enter");
    pressEnterText.setPosition(140, 160);

    w.clear();
    w.draw(gameoverText);
    w.draw(pressEnterText);
    w.display();
}

void game(RenderWindow &w, Player &player, std::vector<Bullet> &bullets, Asteroid &asteroid, GameState &gameState){
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

    if(player.getBounds().intersects(asteroid.getBounds())){
        gameState = GameState::GAMEOVER;
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

int main(){
    //Render window and limit fps
    RenderWindow w(VideoMode(400, 300), "Ship");
    Vector2u originalSize = w.getSize();
    float aspectRatio = float(originalSize.x) / float(originalSize.y);

    w.setFramerateLimit(60);
    
    Player player;
    std::vector<Bullet> bullets; 
    Asteroid asteroid;
    GameState gameState = GameState::MENU;

    //Handles window events, like closing, losing focus, resizing (still working on this) and game states
    while(w.isOpen()){
        Event event;
        while (w.pollEvent(event)){
            if(event.type == Event::Closed)
                w.close();
            if(event.type == Event::Resized){
                Vector2u newSize = w.getSize();
                float newAspectRatio = float(newSize.x) / float(newSize.y);

                if(newAspectRatio != aspectRatio){
                    unsigned int newWidth = newSize.x;
                    unsigned int newHeight = uintmax_t (newWidth / aspectRatio);

                    w.setSize(Vector2u(newWidth, newHeight));
                }
            }
            if(event.type == Event::LostFocus){
                w.waitEvent(event);
            }
            if(event.type == Event::KeyPressed && event.key.code == Keyboard::Enter){
                switch(gameState){
                    case GameState::MENU:
                        gameState = GameState::GAME;
                        break;

                    case GameState::GAME:
                        gameState = GameState::PAUSE;
                        break;

                    case GameState::PAUSE:
                        gameState = GameState::GAME;
                        break;
                    
                    case GameState::GAMEOVER:
                        gameState = GameState::MENU;
                        break;
                }
            }
        }
        //Handles game states
        switch(gameState){
            case GameState::MENU:
                menu(w);
                break;

            case GameState::GAME:
                game(w, player, bullets, asteroid, gameState);
                break;

            case GameState::PAUSE:
                pause(w);
                break;

            case GameState::GAMEOVER:
                gameover(w);
                player.resetPos();
                asteroid.resetPos();
                bullets.clear();
                break;
        }
    }
    return 0;
}