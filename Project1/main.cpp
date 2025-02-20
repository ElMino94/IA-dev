#include <SFML/Graphics.hpp>
#include "Player.hpp"
#include "Enemy.hpp"
#include "boost_pad.hpp"  
#include "Grid.hpp"
#include <vector>
#include "Hunter.hpp"
#include "Patrol.hpp"

using namespace sf;
using namespace std;

const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 600;

int main() {
    RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Jeu SFML - IA Ennemis");
    window.setFramerateLimit(60);

    Player player(200, 400);

    vector<Patrol> enemies;
    vector<Hunter> hunters;
    vector<BoostPad> boostPads; 

    Grid grid;

    grid.loadFromFile("map.txt");

    for (const auto& pos : grid.patrolPositions) {
        enemies.emplace_back(pos.x, pos.y);
    }
    for (const auto& pos : grid.hunter_Positions) {
        hunters.emplace_back(pos.x, pos.y);
    }
    for (const auto& pos : grid.boost_Positions) {
        boostPads.emplace_back(pos.x, pos.y);
    }
    enemies[0].setWaypoints({ {400, 200}, {400, 400}, {600, 400}, {600, 200} });
    enemies[1].setWaypoints({ {600, 200}, {600, 400}, {400, 400}, {400, 200} });

    Clock clock;

    while (window.isOpen()) {
        Time dt = clock.restart();
        float deltaTime = dt.asSeconds();

        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed)
                window.close();
            if (event.type == sf::Event::MouseButtonPressed) {
                if (event.mouseButton.button == sf::Mouse::Left) {
                    grid.handleClick(event.mouseButton.x, event.mouseButton.y);
                }
            }
        }

        player.update(deltaTime, grid, player.shape.getPosition());
        for (auto& enemy : enemies) {
            enemy.update(deltaTime, grid, player.getPosition());
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
        for (auto& enemy : enemies) {
			enemy.update(deltaTime, grid, player.getPosition());
            window.draw(enemy.shape);
        }
        for (auto& hunter : hunters) {
            window.draw(hunter.shape);
            hunter.check_collision(player);
        }      
        window.display();
    }
    return 0;
}
