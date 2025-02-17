#include <SFML/Graphics.hpp>
#include "Player.hpp"
#include "Enemy.hpp"
#include "boost_pad.hpp"  
#include "Grid.hpp"
#include <vector>
#include "Hunter.hpp"

const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 600;

int main() {
    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Jeu SFML - IA Ennemis");
    window.setFramerateLimit(60);

    Player player(200, 400);
    std::vector<Enemy> enemies = { Enemy(100, 100), Enemy(700, 100) };
    std::vector<Hunter> hunters = { Hunter(150, 100) };
    std::vector<BoostPad> boostPads = { BoostPad(300, 500) }; 
    Grid grid;
    grid.loadFromFile("map.txt");

    sf::Clock clock;

    while (window.isOpen()) {
        sf::Time dt = clock.restart();
        float deltaTime = dt.asSeconds();

        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        player.update(deltaTime, grid, player.shape.getPosition());
        for (auto& enemy : enemies) {
            enemy.update(deltaTime, grid, player.shape.getPosition());
            enemy.check_collision(player);  
        }
        for (auto& hunter : hunters) {
            hunter.update(deltaTime, grid, player.shape.getPosition());
        }

        for (auto it = boostPads.begin(); it != boostPads.end(); ) {
            if (it->checkCollision(player.shape)) {
                player.activateBoost(2.f);  
                it = boostPads.erase(it);  
            }
            else {
                ++it;  
            }
        }

        window.clear();
        grid.draw(window);
        for (const auto& boostPad : boostPads) {
            boostPad.draw(window); 
        }
        window.draw(player.shape);
        for (const auto& enemy : enemies) {
            window.draw(enemy.shape);
        }
        for (const auto& hunter : hunters) {
            window.draw(hunter.shape);
        }
        window.display();
    }
    return 0;
}
