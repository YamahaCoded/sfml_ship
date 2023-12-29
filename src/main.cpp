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

int score = 0;

void drawText(RenderWindow &w, const std::string &text, const Vector2f &position, int characterSize = 15){
    //Function to make it simple to draw text
    Font font;
    if (!font.loadFromFile("./resources/PressStart2P-Regular.ttf")){
    }

    Text displayText;
    displayText.setFont(font);
    displayText.setCharacterSize(characterSize);
    displayText.setFillColor(Color::White);
    displayText.setString(text);
    displayText.setPosition(position);
    w.draw(displayText);
}

void menu(RenderWindow &w){
    w.clear();
    drawText(w, "Ship!", Vector2f(110, 100), 40);
    drawText(w, "Press Enter to Start", Vector2f(100, 160), 10);
    w.display();
}

void pause(RenderWindow &w){
    w.clear();
    drawText(w, "Paused!", Vector2f(70, 100), 40);
    drawText(w, "Press Enter to Resume", Vector2f(90, 160), 10);
    w.display();
}

void gameover(RenderWindow &w){
    w.clear();
    drawText(w, "GameOver", Vector2f(45, 100), 40);
    drawText(w, "Press Enter", Vector2f(140, 160), 10);
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

    //Checks Collisions and Gameover
    auto bulletIt = bullets.begin();
    for(auto &bullet : bullets){
        FloatRect bulletBounds = bullet.getBounds();
        FloatRect asteroidBounds = asteroid.getBounds();

        if(bulletBounds.intersects(asteroidBounds)){
            asteroid.resetPos();
            bulletIt = bullets.erase(bulletIt);
            score += 5;
        }
    }

    if(player.getBounds().intersects(asteroid.getBounds())){
        gameState = GameState::GAMEOVER;
        score = 0;
    }

    //Clear window
    w.clear();

    //Draw stuff if needed
    player.draw(w);
    asteroid.draw(w);
    drawText(w, "Score: " + std::to_string(score), Vector2f(10, 10), 12);

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